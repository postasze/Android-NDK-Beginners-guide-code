#include "Log.hpp"
#include "MoveableBody.hpp"

static const float MOVE_SPEED = 10.0f / PHYSICS_SCALE;

MoveableBody::MoveableBody(android_app* pApplication,
      InputManager& pInputManager, PhysicsManager& pPhysicsManager) :
  mInputManager(pInputManager),
  mPhysicsManager(pPhysicsManager),
  mBody(NULL), mTarget(NULL) {
}

b2Body* MoveableBody::registerMoveableBody(Location& pLocation,
        int32_t pSizeX, int32_t pSizeY) {
    mBody = mPhysicsManager.loadBody(pLocation, 0x2, 0x1, pSizeX,
            pSizeY, 0.0f);
    mTarget = mPhysicsManager.loadTarget(mBody);
    mInputManager.setRefPoint(&pLocation);
    return mBody;
}

void MoveableBody::initialize() {
    mBody->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
}

void MoveableBody::update() {
    b2Vec2 target = mBody->GetPosition() + b2Vec2(
        mInputManager.getDirectionX() * MOVE_SPEED,
        mInputManager.getDirectionY() * MOVE_SPEED);
    mTarget->SetTarget(target);
}
