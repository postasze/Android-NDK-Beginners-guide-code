#ifndef _PACKT_EVENTLOOP_HPP_
#define _PACKT_EVENTLOOP_HPP_

#include <android_native_app_glue.h>

class EventLoop {
public:
    EventLoop(android_app* pApplication);

    void run();

private:
    android_app* mApplication;
};
#endif
