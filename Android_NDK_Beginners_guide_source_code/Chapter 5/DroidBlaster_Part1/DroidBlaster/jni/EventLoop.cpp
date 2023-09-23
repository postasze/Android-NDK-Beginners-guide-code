#include "EventLoop.hpp"
#include "Log.hpp"

EventLoop::EventLoop(android_app* pApplication):
        mApplication(pApplication)
{}

void EventLoop::run() {
    int32_t result; int32_t events;
    android_poll_source* source;

    // Makes sure native glue is not stripped by the linker.
    app_dummy();

    Log::info("Starting event loop");
    while (true) {
        // Event processing loop.
        while ((result = ALooper_pollAll(-1, NULL, &events,
                (void**) &source)) >= 0) {
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
    }
}
