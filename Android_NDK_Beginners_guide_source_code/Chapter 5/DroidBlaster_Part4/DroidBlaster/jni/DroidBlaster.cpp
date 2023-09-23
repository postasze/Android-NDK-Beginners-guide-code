#include "DroidBlaster.hpp"
#include "Log.hpp"

#include <unistd.h>

static const int32_t SHIP_SIZE = 64;
static const int32_t ASTEROID_COUNT = 16;
static const int32_t ASTEROID_SIZE = 64;

DroidBlaster::DroidBlaster(android_app* pApplication):
    mTimeManager(),
    mGraphicsManager(pApplication),
    mPhysicsManager(mTimeManager, mGraphicsManager),
    mEventLoop(pApplication, *this),

    mAsteroids(pApplication, mTimeManager, mGraphicsManager,
            mPhysicsManager),
    mShip(pApplication, mGraphicsManager) {
    Log::info("Creating DroidBlaster");

    GraphicsElement* shipGraphics = mGraphicsManager.registerElement(
            SHIP_SIZE, SHIP_SIZE);
    mShip.registerShip(shipGraphics);

    // Creates asteroids.
    for (int32_t i = 0; i < ASTEROID_COUNT; ++i) {
        GraphicsElement* asteroidGraphics =
                    mGraphicsManager.registerElement(ASTEROID_SIZE,
                                                    ASTEROID_SIZE);
        mAsteroids.registerAsteroid(
                asteroidGraphics->location, ASTEROID_SIZE,
                ASTEROID_SIZE);
    }
}

void DroidBlaster::run() {
    mEventLoop.run();
}

status DroidBlaster::onActivate() {
    Log::info("Activating DroidBlaster");

    // Starts managers.
    if (mGraphicsManager.start() != STATUS_OK) return STATUS_KO;

    // Initializes game objects.
    mAsteroids.initialize();
    mShip.initialize();

    mTimeManager.reset();
    return STATUS_OK;
}

void DroidBlaster::onDeactivate() {
    Log::info("Deactivating DroidBlaster");
}

status DroidBlaster::onStep() {
    mTimeManager.update();
    mPhysicsManager.update();

    // Updates modules.
    mAsteroids.update();

    return mGraphicsManager.update();
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
