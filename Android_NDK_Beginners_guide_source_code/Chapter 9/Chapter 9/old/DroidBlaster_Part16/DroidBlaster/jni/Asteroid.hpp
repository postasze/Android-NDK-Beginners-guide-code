#ifndef _PACKT_ASTEROID_HPP_
#define _PACKT_ASTEROID_HPP_

#include "GraphicsManager.hpp"
#include "PhysicsManager.hpp"
#include "TimeManager.hpp"
#include "Types.hpp"

#include <vector>

class Asteroid {
public:
    Asteroid(android_app* pApplication,
        TimeManager& pTimeManager, GraphicsManager& pGraphicsManager,
        PhysicsManager& pPhysicsManager);

    void registerAsteroid(Location& pLocation, int32_t pSizeX,
            int32_t pSizeY);

    void initialize();
    void update();

private:
    Asteroid(const Asteroid&);
    void operator=(const Asteroid&);

    void spawn(PhysicsBody* pBody);

    TimeManager& mTimeManager;
    GraphicsManager& mGraphicsManager;
    PhysicsManager& mPhysicsManager;

    std::vector<PhysicsBody*> mBodies;
    float mMinBound;
    float mUpperBound; float mLowerBound;
    float mLeftBound; float mRightBound;
};
#endif
