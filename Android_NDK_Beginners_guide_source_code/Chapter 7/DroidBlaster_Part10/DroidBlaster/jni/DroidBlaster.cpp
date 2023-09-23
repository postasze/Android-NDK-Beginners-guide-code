#include "DroidBlaster.hpp"
#include "Log.hpp"

#include <unistd.h>

static const int32_t SHIP_SIZE = 64;
static const int32_t SHIP_FRAME_1 = 0;
static const int32_t SHIP_FRAME_COUNT = 8;
static const float SHIP_ANIM_SPEED = 8.0f;

static const int32_t ASTEROID_COUNT = 16;
static const int32_t ASTEROID_SIZE = 64;
static const int32_t ASTEROID_FRAME_1 = 0;
static const int32_t ASTEROID_FRAME_COUNT = 16;
static const float ASTEROID_MIN_ANIM_SPEED = 8.0f;
static const float ASTEROID_ANIM_SPEED_RANGE = 16.0f;

static const int32_t STAR_COUNT = 50;

DroidBlaster::DroidBlaster(android_app* pApplication):
    mTimeManager(),
    mGraphicsManager(pApplication),
    mPhysicsManager(mTimeManager, mGraphicsManager),
    mSoundManager(pApplication),
    mEventLoop(pApplication, *this),

    mAsteroidTexture(pApplication, "droidblaster/asteroid.png"),
    mShipTexture(pApplication, "droidblaster/ship.png"),
    mStarTexture(pApplication, "droidblaster/star.png"),

    mAsteroids(pApplication, mTimeManager, mGraphicsManager,
            mPhysicsManager),
    mShip(pApplication, mGraphicsManager),
    mStarField(pApplication, mTimeManager, mGraphicsManager,
            STAR_COUNT, mStarTexture),
    mSpriteBatch(mTimeManager, mGraphicsManager) {
    Log::info("Creating DroidBlaster");

//    GraphicsElement* shipGraphics = mGraphicsManager.registerElement(
//            SHIP_SIZE, SHIP_SIZE);
    Sprite* shipGraphics = mSpriteBatch.registerSprite(mShipTexture,
            SHIP_SIZE, SHIP_SIZE);
    shipGraphics->setAnimation(SHIP_FRAME_1, SHIP_FRAME_COUNT,
            SHIP_ANIM_SPEED, true);
//    mShip.registerShip(shipGraphics);
    mShip.registerShip(shipGraphics);

    // Creates asteroids.
    for (int32_t i = 0; i < ASTEROID_COUNT; ++i) {
//        GraphicsElement* asteroidGraphics =
//                    mGraphicsManager.registerElement(ASTEROID_SIZE,
//                                                    ASTEROID_SIZE);
        Sprite* asteroidGraphics = mSpriteBatch.registerSprite(
                mAsteroidTexture, ASTEROID_SIZE, ASTEROID_SIZE);
        float animSpeed = ASTEROID_MIN_ANIM_SPEED + RAND(ASTEROID_ANIM_SPEED_RANGE);
        asteroidGraphics->setAnimation(ASTEROID_FRAME_1,
                ASTEROID_FRAME_COUNT, animSpeed, true);
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
    if (mSoundManager.start() != STATUS_OK) return STATUS_KO;

    // Initializes game objects.
    mAsteroids.initialize();
    mShip.initialize();

    mTimeManager.reset();
    return STATUS_OK;
}

void DroidBlaster::onDeactivate() {
    Log::info("Deactivating DroidBlaster");
    mGraphicsManager.stop();
    mSoundManager.stop();
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
