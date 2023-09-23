#include "DroidBlaster.hpp"
#include "Log.hpp"

#include <unistd.h>

DroidBlaster::DroidBlaster(android_app* pApplication) :
    mEventLoop(pApplication, *this) {
    Log::info("Creating DroidBlaster");
}

void DroidBlaster::run() {
    mEventLoop.run();
}

status DroidBlaster::onActivate() {
    Log::info("Activating DroidBlaster");
    return STATUS_OK;
}

void DroidBlaster::onDeactivate() {
    Log::info("Deactivating DroidBlaster");
}

status DroidBlaster::onStep() {
//    Log::info("Starting step");
    usleep(300000);
//    Log::info("Stepping done");
    return STATUS_OK;
}

void DroidBlaster::onStart() {
    Log::info("onStart");
}

void DroidBlaster::onResume() {
    Log::info("onResume");
}

void DroidBlaster::onPause() {
    Log::info("onPause");
}

void DroidBlaster::onStop() {
    Log::info("onStop");
}

void DroidBlaster::onDestroy() {
    Log::info("onDestroy");
}

void DroidBlaster::onSaveInstanceState(void** pData, size_t* pSize) {
    Log::info("onSaveInstanceState");
}

void DroidBlaster::onConfigurationChanged() {
    Log::info("onConfigurationChanged");
}

void DroidBlaster::onLowMemory() {
    Log::info("onLowMemory");
}

void DroidBlaster::onCreateWindow() {
    Log::info("onCreateWindow");
}

void DroidBlaster::onDestroyWindow() {
    Log::info("onDestroyWindow");
}

void DroidBlaster::onGainFocus() {
    Log::info("onGainFocus");
}

void DroidBlaster::onLostFocus() {
    Log::info("onLostFocus");
}
