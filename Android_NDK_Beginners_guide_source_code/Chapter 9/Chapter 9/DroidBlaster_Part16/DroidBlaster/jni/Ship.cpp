#include "Log.hpp"
#include "Ship.hpp"

static const float INITAL_X = 0.5f;
static const float INITAL_Y = 0.25f;

Ship::Ship(android_app* pApplication,
        GraphicsManager& pGraphicsManager,
        SoundManager& pSoundManager) :
  mGraphicsManager(pGraphicsManager),
  mGraphics(NULL),
  mSoundManager(pSoundManager),
  mCollisionSound(NULL) {
}

//void Ship::registerShip(GraphicsElement* pGraphics) {
//    mGraphics = pGraphics;
//}

void Ship::registerShip(Sprite* pGraphics, Sound* pCollisionSound) {
    mGraphics = pGraphics;
    mCollisionSound = pCollisionSound;
}

void Ship::initialize() {
    mGraphics->location.x = INITAL_X
            * mGraphicsManager.getRenderWidth();
    mGraphics->location.y = INITAL_Y
            * mGraphicsManager.getRenderHeight();
    mSoundManager.playSound(mCollisionSound);
}
