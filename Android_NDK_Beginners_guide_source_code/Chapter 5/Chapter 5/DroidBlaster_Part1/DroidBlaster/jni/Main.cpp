#include "EventLoop.hpp"
#include "Log.hpp"

void android_main(android_app* pApplication) {
    EventLoop(pApplication).run();
}
