#ifndef _PACKT_INPUTHANDLER_HPP_
#define _PACKT_INPUTHANDLER_HPP_

#include <android/input.h>

class InputHandler {
public:
    virtual ~InputHandler() {};

    virtual bool onTouchEvent(AInputEvent* pEvent) = 0;
    virtual bool onKeyboardEvent(AInputEvent* pEvent) = 0;
    virtual bool onTrackballEvent(AInputEvent* pEvent) = 0;
};
#endif
