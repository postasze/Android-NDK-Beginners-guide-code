#ifndef _PACKT_INPUTMANAGER_HPP_
#define _PACKT_INPUTMANAGER_HPP_

#include "Configuration.hpp"
#include "GraphicsManager.hpp"
#include "InputHandler.hpp"
#include "Types.hpp"

#include <android_native_app_glue.h>

class InputManager : public InputHandler {
public:
    InputManager(android_app* pApplication,
            GraphicsManager& pGraphicsManager);

    float getDirectionX() { return mDirectionX; };
    float getDirectionY() { return mDirectionY; };
    void setRefPoint(Location* pRefPoint) { mRefPoint = pRefPoint; };

    void start();

protected:
    bool onTouchEvent(AInputEvent* pEvent);
    bool onKeyboardEvent(AInputEvent* pEvent);
    bool onTrackballEvent(AInputEvent* pEvent);
    bool onAccelerometerEvent(ASensorEvent* pEvent);
    void toScreenCoord(screen_rot pRotation,
        ASensorVector* pCanonical, ASensorVector* pScreen);

private:
    InputManager(const InputManager&);
    void operator=(const InputManager&);

    android_app* mApplication;
    GraphicsManager& mGraphicsManager;

    // Input values.
    float mScaleFactor;
    float mDirectionX, mDirectionY;
    // Reference point to evaluate touch distance.
    Location* mRefPoint;
    screen_rot mRotation;
};
#endif
