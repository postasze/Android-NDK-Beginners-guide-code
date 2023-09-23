#include "Asteroid.hpp"
#include "Log.hpp"

static const float BOUNDS_MARGIN = 128;
static const float MIN_VELOCITY = 150.0f, VELOCITY_RANGE = 600.0f;

Asteroid::Asteroid(android_app* pApplication,
        TimeManager& pTimeManager, GraphicsManager& pGraphicsManager,
        PhysicsManager& pPhysicsManager) :
    mTimeManager(pTimeManager),
    mGraphicsManager(pGraphicsManager),
    mPhysicsManager(pPhysicsManager),
    mBodies(),
    mMinBound(0.0f),
    mUpperBound(0.0f), mLowerBound(0.0f),
    mLeftBound(0.0f), mRightBound(0.0f)
    {
}

void Asteroid::registerAsteroid(Location& pLocation,
        int32_t pSizeX, int32_t pSizeY) {
    mBodies.push_back(mPhysicsManager.loadBody(pLocation,
            pSizeX, pSizeY));
}

void Asteroid::initialize() {
    mMinBound = mGraphicsManager.getRenderHeight();
    mUpperBound = mMinBound * 2;
    mLowerBound = -BOUNDS_MARGIN;
    mLeftBound = -BOUNDS_MARGIN;
    mRightBound = (mGraphicsManager.getRenderWidth() + BOUNDS_MARGIN);

    std::vector<PhysicsBody*>::iterator bodyIt;
    for (bodyIt = mBodies.begin(); bodyIt < mBodies.end(); ++bodyIt) {
        spawn(*bodyIt);
    }
}

void Asteroid::update() {
    std::vector<PhysicsBody*>::iterator bodyIt;
    for (bodyIt = mBodies.begin(); bodyIt < mBodies.end(); ++bodyIt) {
        PhysicsBody* body = *bodyIt;
        if ((body->location->x < mLeftBound)
         || (body->location->x > mRightBound)
         || (body->location->y < mLowerBound)
         || (body->location->y > mUpperBound)) {
            spawn(body);
        }
    }
}

void Asteroid::spawn(PhysicsBody* pBody) {
    float velocity = -(RAND(VELOCITY_RANGE) + MIN_VELOCITY);
    float posX = RAND(mGraphicsManager.getRenderWidth());
    float posY = RAND(mGraphicsManager.getRenderHeight())
                  + mGraphicsManager.getRenderHeight();

    pBody->velocityX = 0.0f;
    pBody->velocityY = velocity;
    pBody->location->x = posX;
    pBody->location->y = posY;
}
