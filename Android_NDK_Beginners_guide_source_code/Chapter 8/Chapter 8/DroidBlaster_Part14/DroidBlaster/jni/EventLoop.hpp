#ifndef _PACKT_EVENTLOOP_HPP_
#define _PACKT_EVENTLOOP_HPP_

#include "ActivityHandler.hpp"
#include "InputHandler.hpp"

#include <android_native_app_glue.h>

class EventLoop {
public:
    EventLoop(android_app* pApplication,
            ActivityHandler& pActivityHandler,
            InputHandler& pInputHandler);

    void run();

private:
    void activate();
    void deactivate();

    void processAppEvent(int32_t pCommand);
    int32_t processInputEvent(AInputEvent* pEvent);

    static void callback_appEvent(android_app* pApplication,
        int32_t pCommand);
    static int32_t callback_input(android_app* pApplication,
        AInputEvent* pEvent);

private:
    android_app* mApplication;
    bool mEnabled;
    bool mQuit;

    ActivityHandler& mActivityHandler;
    InputHandler& mInputHandler;
};
#endif
