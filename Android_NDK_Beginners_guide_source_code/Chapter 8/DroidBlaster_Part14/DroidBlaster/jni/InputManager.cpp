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


bool InputManager::onKeyboardEvent(AInputEvent* pEvent) {
    #ifdef INPUTMANAGER_LOG_EVENTS
    packt_Log_debug("AKeyEvent_getAction=%d", AKeyEvent_getAction(pEvent));
    packt_Log_debug("AKeyEvent_getFlags=%d", AKeyEvent_getFlags(pEvent));
    packt_Log_debug("AKeyEvent_getKeyCode=%d", AKeyEvent_getKeyCode(pEvent));
    packt_Log_debug("AKeyEvent_getScanCode=%d", AKeyEvent_getScanCode(pEvent));
    packt_Log_debug("AKeyEvent_getMetaState=%d", AKeyEvent_getMetaState(pEvent));
    packt_Log_debug("AKeyEvent_getRepeatCount=%d", AKeyEvent_getRepeatCount(pEvent));
    packt_Log_debug("AKeyEvent_getDownTime=%lld", AKeyEvent_getDownTime(pEvent));
    packt_Log_debug("AKeyEvent_getEventTime=%lld", AKeyEvent_getEventTime(pEvent));
    #endif
    static const float ORTHOGONAL_MOVE = 1.0f;

    if (AKeyEvent_getAction(pEvent) == AKEY_EVENT_ACTION_DOWN) {
        switch (AKeyEvent_getKeyCode(pEvent)) {
        case AKEYCODE_DPAD_LEFT:
            mDirectionX = -ORTHOGONAL_MOVE;
            return true;
        case AKEYCODE_DPAD_RIGHT:
            mDirectionX = ORTHOGONAL_MOVE;
            return true;
        case AKEYCODE_DPAD_DOWN:
            mDirectionY = -ORTHOGONAL_MOVE;
            return true;
        case AKEYCODE_DPAD_UP:
            mDirectionY = ORTHOGONAL_MOVE;
            return true;
        }
    } else {
        switch (AKeyEvent_getKeyCode(pEvent)) {
        case AKEYCODE_DPAD_LEFT:
        case AKEYCODE_DPAD_RIGHT:
            mDirectionX = 0.0f;
            return true;
        case AKEYCODE_DPAD_DOWN:
        case AKEYCODE_DPAD_UP:
            mDirectionY = 0.0f;
            return true;
        }
    }
    return false;
}

bool InputManager::onTrackballEvent(AInputEvent* pEvent) {
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
    static const float ORTHOGONAL_MOVE = 1.0f;
    static const float DIAGONAL_MOVE   = 0.707f;
    static const float THRESHOLD       = (1/100.0f);

     if (AMotionEvent_getAction(pEvent) == AMOTION_EVENT_ACTION_MOVE) {
        float directionX = AMotionEvent_getX(pEvent, 0);
        float directionY = AMotionEvent_getY(pEvent, 0);
        float horizontal, vertical;

        if (directionX < -THRESHOLD) {
            if (directionY < -THRESHOLD) {
                horizontal = -DIAGONAL_MOVE;
                vertical   = DIAGONAL_MOVE;
            } else if (directionY > THRESHOLD) {
                horizontal = -DIAGONAL_MOVE;
                vertical   = -DIAGONAL_MOVE;
            } else {
                horizontal = -ORTHOGONAL_MOVE;
                vertical   = 0.0f;
            }
        } else if (directionX > THRESHOLD) {
            if (directionY < -THRESHOLD) {
                horizontal = DIAGONAL_MOVE;
                vertical   = DIAGONAL_MOVE;
            } else if (directionY > THRESHOLD) {
                horizontal = DIAGONAL_MOVE;
                vertical   = -DIAGONAL_MOVE;
            } else {
                horizontal = ORTHOGONAL_MOVE;
                vertical   = 0.0f;
            }
        } else if (directionY < -THRESHOLD) {
            horizontal = 0.0f;
            vertical   = ORTHOGONAL_MOVE;
        } else if (directionY > THRESHOLD) {
            horizontal = 0.0f;
            vertical   = -ORTHOGONAL_MOVE;
        }

        // Ends movement if there is a counter movement.
        if ((horizontal < 0.0f) && (mDirectionX > 0.0f)) {
            mDirectionX = 0.0f;
        } else if ((horizontal > 0.0f) && (mDirectionX < 0.0f)) {
            mDirectionX = 0.0f;
        } else {
            mDirectionX = horizontal;
        }

        if ((vertical < 0.0f) && (mDirectionY > 0.0f)) {
            mDirectionY = 0.0f;
        } else if ((vertical > 0.0f) && (mDirectionY < 0.0f)) {
            mDirectionY = 0.0f;
        } else {
            mDirectionY = vertical;
        }
    } else {
        mDirectionX = 0.0f; mDirectionY = 0.0f;
    }
    return true;
}
