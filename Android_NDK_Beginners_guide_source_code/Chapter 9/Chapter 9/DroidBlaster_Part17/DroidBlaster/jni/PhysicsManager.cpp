#include "PhysicsManager.hpp"
#include "Log.hpp"

static const int32_t VELOCITY_ITER = 6;
static const int32_t POSITION_ITER = 2;

PhysicsManager::PhysicsManager(TimeManager& pTimeManager,
        GraphicsManager& pGraphicsManager) :
  mTimeManager(pTimeManager), mGraphicsManager(pGraphicsManager),
  mWorld(b2Vec2_zero), mBodies(),
  mLocations(),
  mBoundsBodyObj(NULL) {
    Log::info("Creating PhysicsManager.");
    mWorld.SetContactListener(this);
}

PhysicsManager::~PhysicsManager() {
    std::vector<b2Body*>::iterator bodyIt;
    for (bodyIt = mBodies.begin(); bodyIt < mBodies.end(); ++bodyIt) {
        delete (PhysicsCollision*) (*bodyIt)->GetUserData();
    }
}

void PhysicsManager::start() {
    if (mBoundsBodyObj == NULL) {
        b2BodyDef boundsBodyDef;
        b2ChainShape boundsShapeDef;
        float renderWidth = mGraphicsManager.getRenderWidth()
                                / PHYSICS_SCALE;
        float renderHeight = mGraphicsManager.getRenderHeight()
                                / PHYSICS_SCALE;
        b2Vec2 boundaries[4];
        boundaries[0].Set(0.0f, 0.0f);
        boundaries[1].Set(renderWidth, 0.0f);
        boundaries[2].Set(renderWidth, renderHeight);
        boundaries[3].Set(0.0f, renderHeight);
        boundsShapeDef.CreateLoop(boundaries, 4);

        mBoundsBodyObj = mWorld.CreateBody(&boundsBodyDef);
        mBoundsBodyObj->CreateFixture(&boundsShapeDef, 0);
    }
}

b2Body* PhysicsManager::loadBody(Location& pLocation,
    uint16 pCategory, uint16 pMask, int32_t pSizeX, int32_t pSizeY,
    float pRestitution) {
    PhysicsCollision* userData = new PhysicsCollision();

    b2BodyDef mBodyDef; b2Body* mBodyObj;
    b2CircleShape mShapeDef; b2FixtureDef mFixtureDef;

    mBodyDef.type = b2_dynamicBody;
    mBodyDef.userData = userData;
    mBodyDef.awake = true;
    mBodyDef.fixedRotation = true;

    // Box2D requires half dimension (from center to borders).
    mShapeDef.m_p = b2Vec2_zero;
    int32_t diameter = (pSizeX + pSizeY) / 2;
    mShapeDef.m_radius = diameter / (2.0f * PHYSICS_SCALE);

    mFixtureDef.shape = &mShapeDef;
    mFixtureDef.density = 1.0f;
    mFixtureDef.friction = 0.0f;
    mFixtureDef.restitution = pRestitution;
    mFixtureDef.filter.categoryBits = pCategory;
    mFixtureDef.filter.maskBits = pMask;
    mFixtureDef.userData = userData;

    mBodyObj = mWorld.CreateBody(&mBodyDef);
    mBodyObj->CreateFixture(&mFixtureDef);
    mBodyObj->SetUserData(userData);
    mLocations.push_back(&pLocation);
    mBodies.push_back(mBodyObj);
    return mBodyObj;
}

b2MouseJoint* PhysicsManager::loadTarget(b2Body* pBody) {
    b2BodyDef emptyBodyDef;
    b2Body* emptyBody = mWorld.CreateBody(&emptyBodyDef);

    b2MouseJointDef mouseJointDef;
    mouseJointDef.bodyA = emptyBody;
    mouseJointDef.bodyB = pBody;
    mouseJointDef.target = b2Vec2(0.0f, 0.0f);
    mouseJointDef.maxForce = 50.0f * pBody->GetMass();
    mouseJointDef.dampingRatio = 0.15f;
    mouseJointDef.frequencyHz = 3.5f;

    return (b2MouseJoint*) mWorld.CreateJoint(&mouseJointDef);
}

void PhysicsManager::update() {
    // Clears collision flags.
    int32_t size = mBodies.size();
    for (int32_t i = 0; i < size; ++i) {
        PhysicsCollision* physicsCollision =
               ((PhysicsCollision*) mBodies[i]->GetUserData());
        physicsCollision->collide = false;
    }
    // Updates simulation.
    float timeStep = mTimeManager.elapsed();
    mWorld.Step(timeStep, VELOCITY_ITER, POSITION_ITER);

    // Caches the new state.
    for (int32_t i = 0; i < size; ++i) {
        const b2Vec2& position = mBodies[i]->GetPosition();
        mLocations[i]->x = position.x * PHYSICS_SCALE;
        mLocations[i]->y = position.y * PHYSICS_SCALE;
    }
}

void PhysicsManager::BeginContact(b2Contact* pContact) {
    void* userDataA = pContact->GetFixtureA()->GetUserData();
    void* userDataB = pContact->GetFixtureB()->GetUserData();
    if (userDataA != NULL && userDataB != NULL) {
        ((PhysicsCollision*)userDataA)->collide = true;
        ((PhysicsCollision*)userDataB)->collide = true;
    }
}
