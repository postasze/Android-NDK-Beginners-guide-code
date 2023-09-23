#include "Log.hpp"
#include "Ship.hpp"

static const float INITAL_X = 0.5f;
static const float INITAL_Y = 0.25f;

Ship::Ship(android_app* pApplication,
        GraphicsManager& pGraphicsManager) :
  mGraphicsManager(pGraphicsManager),
  mGraphics(NULL) {
}

//void Ship::registerShip(GraphicsElement* pGraphics) {
//    mGraphics = pGraphics;
//}

void Ship::registerShip(Sprite* pGraphics) {
    mGraphics = pGraphics;
}

void Ship::initialize() {
    mGraphics->location.x = INITAL_X
            * mGraphicsManager.getRenderWidth();
    mGraphics->location.y = INITAL_Y
            * mGraphicsManager.getRenderHeight();
}
