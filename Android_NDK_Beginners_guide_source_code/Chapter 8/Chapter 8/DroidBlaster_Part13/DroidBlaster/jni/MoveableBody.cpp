#include "Log.hpp"
#include "MoveableBody.hpp"

MoveableBody::MoveableBody(android_app* pApplication,
      InputManager& pInputManager, PhysicsManager& pPhysicsManager) :
  mInputManager(pInputManager),
  mPhysicsManager(pPhysicsManager),
  mBody(NULL) {
}

PhysicsBody* MoveableBody::registerMoveableBody(Location& pLocation,
        int32_t pSizeX, int32_t pSizeY) {
    mBody = mPhysicsManager.loadBody(pLocation, pSizeX, pSizeY);
    mInputManager.setRefPoint(&pLocation);
    return mBody;
}

void MoveableBody::initialize() {
    mBody->velocityX = 0.0f;
    mBody->velocityY = 0.0f;
}

void MoveableBody::update() {
    static const float MOVE_SPEED = 320.0f;
    mBody->velocityX = mInputManager.getDirectionX() * MOVE_SPEED;
    mBody->velocityY = mInputManager.getDirectionY() * MOVE_SPEED;
}
