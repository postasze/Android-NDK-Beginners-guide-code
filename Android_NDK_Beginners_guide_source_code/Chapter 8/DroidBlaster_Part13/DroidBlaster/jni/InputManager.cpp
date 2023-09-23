#include "InputManager.hpp"
#include "Log.hpp"

#include <android_native_app_glue.h>
#include <cmath>

InputManager::InputManager(android_app* pApplication,
        GraphicsManager& pGraphicsManager) :
    mApplication(pApplication), mGraphicsManager(pGraphicsManager),
    mDirectionX(0.0f), mDirectionY(0.0f),
    mRefPoint(NULL) {
}

void InputManager::start() {
    Log::info("Starting InputManager.");
    mDirectionX = 0.0f, mDirectionY = 0.0f;
    mScaleFactor = float(mGraphicsManager.getRenderWidth())
                    / float(mGraphicsManager.getScreenWidth());

}

bool InputManager::onTouchEvent(AInputEvent* pEvent) {
    #ifdef INPUTMANAGER_LOG_EVENTS
    packt_Log_debug("AMotionEvent_getAction=%d", AMotionEvent_getAction(pEvent));
    packt_Log_debug("AMotionEvent_getFlags=%d", AMotionEvent_getFlags(pEvent));
    packt_Log_debug("AMotionEvent_getMetaState=%d", AMotionEvent_getMetaState(pEvent));
    packt_Log_debug("AMotionEvent_getEdgeFlags=%d", AMotionEvent_getEdgeFlags(pEvent));
    packt_Log_debug("AMotionEvent_getDownTime=%lld", AMotionEvent_getDownTime(pEvent));
    packt_Log_debug("AMotionEvent_getEventTime=%lld", AMotionEvent_getEventTime(pEvent));
    packt_Log_debug("AMotionEvent_getXOffset=%f", AMotionEvent_getXOffset(pEvent));
    packt_Log_debug("AMotionEvent_getYOffset=%f", AMotionEvent_getYOffset(pEvent));
    packt_Log_debug("AMotionEvent_getXPrecision=%f", AMotionEvent_getXPrecision(pEvent));
    packt_Log_debug("AMotionEvent_getYPrecision=%f", AMotionEvent_getYPrecision(pEvent));
    packt_Log_debug("AMotionEvent_getPointerCount=%d", AMotionEvent_getPointerCount(pEvent));
    packt_Log_debug("AMotionEvent_getRawX=%f", AMotionEvent_getRawX(pEvent, 0));
    packt_Log_debug("AMotionEvent_getRawY=%f", AMotionEvent_getRawY(pEvent, 0));
    packt_Log_debug("AMotionEvent_getX=%f", AMotionEvent_getX(pEvent, 0));
    packt_Log_debug("AMotionEvent_getY=%f", AMotionEvent_getY(pEvent, 0));
    packt_Log_debug("AMotionEvent_getPressure=%f", AMotionEvent_getPressure(pEvent, 0));
    packt_Log_debug("AMotionEvent_getSize=%f", AMotionEvent_getSize(pEvent, 0));
    packt_Log_debug("AMotionEvent_getOrientation=%f", AMotionEvent_getOrientation(pEvent, 0));
    packt_Log_debug("AMotionEvent_getTouchMajor=%f", AMotionEvent_getTouchMajor(pEvent, 0));
    packt_Log_debug("AMotionEvent_getTouchMinor=%f", AMotionEvent_getTouchMinor(pEvent, 0));
    #endif

    static const float TOUCH_MAX_RANGE = 65.0f; // In game units.

    if (mRefPoint != NULL) {
        if (AMotionEvent_getAction(pEvent)
                        == AMOTION_EVENT_ACTION_MOVE) {
            float x = AMotionEvent_getX(pEvent, 0) * mScaleFactor;
            float y = (float(mGraphicsManager.getScreenHeight())
                     - AMotionEvent_getY(pEvent, 0)) * mScaleFactor;
            // Needs a conversion to proper coordinates
            // (origin at bottom/left). Only moveY needs it.
            float moveX = x - mRefPoint->x;
            float moveY = y - mRefPoint->y;
            float moveRange = sqrt((moveX * moveX) + (moveY * moveY));

            if (moveRange > TOUCH_MAX_RANGE) {
                float cropFactor = TOUCH_MAX_RANGE / moveRange;
                moveX *= cropFactor; moveY *= cropFactor;
            }

            mDirectionX = moveX / TOUCH_MAX_RANGE;
            mDirectionY   = moveY / TOUCH_MAX_RANGE;
        } else {
            mDirectionX = 0.0f; mDirectionY = 0.0f;
        }
    }
    return true;
}
