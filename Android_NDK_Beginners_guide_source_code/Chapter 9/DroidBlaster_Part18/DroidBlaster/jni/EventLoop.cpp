#include "EventLoop.hpp"
#include "Log.hpp"

EventLoop::EventLoop(android_app* pApplication,
    ActivityHandler& pActivityHandler, InputHandler& pInputHandler):
        mApplication(pApplication),
        mActivityHandler(pActivityHandler),
        mEnabled(false), mQuit(false),
        mInputHandler(pInputHandler),
        mSensorPollSource(), mSensorManager(NULL),
        mSensorEventQueue(NULL), mAccelerometer(NULL) {
    mApplication->userData = this;
    mApplication->onAppCmd = callback_appEvent;
    mApplication->onInputEvent = callback_input;
}

void EventLoop::run() {
    int32_t result; int32_t events;
    android_poll_source* source;

    // Makes sure native glue is not stripped by the linker.
    app_dummy();

    Log::info("Starting event loop");
    while (true) {
        // Event processing loop.
        while ((result = ALooper_pollAll(mEnabled ? 0 : -1, NULL,
                &events, (void**) &source)) >= 0) {
            // An event has to be processed.
            if (source != NULL) {
                Log::info("Processing an event");
                source->process(mApplication, source);
            }
            // Application is getting destroyed.
            if (mApplication->destroyRequested) {
                Log::info("Exiting event loop");
                return;
            }
        }

        // Steps the application.
        if ((mEnabled) && (!mQuit)) {
            if (mActivityHandler.onStep() != STATUS_OK) {
                mQuit = true;
                ANativeActivity_finish(mApplication->activity);
            }
        }
    }
}

void EventLoop::activate() {
    // Enables activity only if a window is available.
    if ((!mEnabled) && (mApplication->window != NULL)) {
        // Registers sensor queue.
        mSensorPollSource.id = LOOPER_ID_USER;
        mSensorPollSource.app = mApplication;
        mSensorPollSource.process = callback_sensor;
        mSensorManager = ASensorManager_getInstance();
        if (mSensorManager != NULL) {
            mSensorEventQueue = ASensorManager_createEventQueue(
                mSensorManager, mApplication->looper,
                LOOPER_ID_USER, NULL, &mSensorPollSource);
            if (mSensorEventQueue == NULL) goto ERROR;
        }
        activateAccelerometer();

        mQuit = false; mEnabled = true;
        if (mActivityHandler.onActivate() != STATUS_OK) {
            goto ERROR;
        }
    }
    return;

ERROR:
    mQuit = true;
    deactivate();
    ANativeActivity_finish(mApplication->activity);
}

void EventLoop::deactivate() {
    if (mEnabled) {
        deactivateAccelerometer();
        if (mSensorEventQueue != NULL) {
            ASensorManager_destroyEventQueue(mSensorManager,
                mSensorEventQueue);
            mSensorEventQueue = NULL;
        }
        mSensorManager = NULL;

        mActivityHandler.onDeactivate();
        mEnabled = false;
    }
}

void EventLoop::callback_appEvent(android_app* pApplication,
    int32_t pCommand) {
    EventLoop& eventLoop = *(EventLoop*) pApplication->userData;
    eventLoop.processAppEvent(pCommand);
}

void EventLoop::processAppEvent(int32_t pCommand) {
    switch (pCommand) {
    case APP_CMD_CONFIG_CHANGED:
        mActivityHandler.onConfigurationChanged();
        break;
    case APP_CMD_INIT_WINDOW:
        mActivityHandler.onCreateWindow();
        break;
    case APP_CMD_DESTROY:
        mActivityHandler.onDestroy();
        break;
    case APP_CMD_GAINED_FOCUS:
        activate();
        mActivityHandler.onGainFocus();
        break;
    case APP_CMD_LOST_FOCUS:
        mActivityHandler.onLostFocus();
        deactivate();
        break;
    case APP_CMD_LOW_MEMORY:
        mActivityHandler.onLowMemory();
        break;
    case APP_CMD_PAUSE:
        mActivityHandler.onPause();
        deactivate();
        break;
    case APP_CMD_RESUME:
        mActivityHandler.onResume();
        break;
    case APP_CMD_SAVE_STATE:
        mActivityHandler.onSaveInstanceState(
            &mApplication->savedState, &mApplication->savedStateSize);
        break;
    case APP_CMD_START:
        mActivityHandler.onStart();
        break;
    case APP_CMD_STOP:
        mActivityHandler.onStop();
        break;
    case APP_CMD_TERM_WINDOW:
        mActivityHandler.onDestroyWindow();
        deactivate();
        break;
    default:
        break;
    }
}

int32_t EventLoop::callback_input(android_app* pApplication,
    AInputEvent* pEvent) {
    EventLoop& eventLoop = *(EventLoop*) pApplication->userData;
    return eventLoop.processInputEvent(pEvent);
}

int32_t EventLoop::processInputEvent(AInputEvent* pEvent) {
    if (!mEnabled) return 0;

    int32_t eventType = AInputEvent_getType(pEvent);
    switch (eventType) {
    case AINPUT_EVENT_TYPE_MOTION:
        switch (AInputEvent_getSource(pEvent)) {
        case AINPUT_SOURCE_TOUCHSCREEN:
            return mInputHandler.onTouchEvent(pEvent);
            break;

        case AINPUT_SOURCE_TRACKBALL:
            return mInputHandler.onTrackballEvent(pEvent);
            break;
        }
        break;

    case AINPUT_EVENT_TYPE_KEY:
        return mInputHandler.onKeyboardEvent(pEvent);
        break;
    }
    return 0;
}

void EventLoop::callback_sensor(android_app* pApplication,
    android_poll_source* pSource) {
    EventLoop& eventLoop = *(EventLoop*) pApplication->userData;
    eventLoop.processSensorEvent();
}

void EventLoop::processSensorEvent() {
    ASensorEvent event;
    if (!mEnabled) return;

    while (ASensorEventQueue_getEvents(mSensorEventQueue,
                                       &event, 1) > 0) {
        switch (event.type) {
        case ASENSOR_TYPE_ACCELEROMETER:
            mInputHandler.onAccelerometerEvent(&event);
            break;
        }
    }
}

void EventLoop::activateAccelerometer() {
    mAccelerometer = ASensorManager_getDefaultSensor(
        mSensorManager, ASENSOR_TYPE_ACCELEROMETER);
    if (mAccelerometer != NULL) {
        if (ASensorEventQueue_enableSensor(
            mSensorEventQueue, mAccelerometer) < 0) {
            Log::error("Could not enable accelerometer");
            return;
        }

        const char* name = ASensor_getName(mAccelerometer);
        const char* vendor = ASensor_getVendor(mAccelerometer);
        float resolution = ASensor_getResolution(mAccelerometer);
        int32_t minDelay = ASensor_getMinDelay(mAccelerometer);
        Log::info("Activating sensor:");
        Log::info("Name       : %s", name);
        Log::info("Vendor     : %s", vendor);
        Log::info("Resolution : %f", resolution);
        Log::info("Min Delay  : %d", minDelay);

        // Uses maximum refresh rate.
        if (ASensorEventQueue_setEventRate(mSensorEventQueue,
                mAccelerometer, minDelay) < 0) {
            Log::error("Could not set accelerometer rate");
        }
    } else {
        Log::error("No accelerometer found");
    }
}

void EventLoop::deactivateAccelerometer() {
    if (mAccelerometer != NULL) {
        if (ASensorEventQueue_disableSensor(mSensorEventQueue,
                mAccelerometer) < 0) {
            Log::error("Error while deactivating sensor.");
        }
        mAccelerometer = NULL;
    }
}
