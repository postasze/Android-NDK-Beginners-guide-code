#ifndef _PACKT_SHIP_HPP_
#define _PACKT_SHIP_HPP_

#include "GraphicsManager.hpp"
#include "Sprite.hpp"
#include "PhysicsManager.hpp"
#include "SoundManager.hpp"
#include "Sound.hpp"

class Ship {
public:
    Ship(android_app* pApplication,
         GraphicsManager& pGraphicsManager,
         SoundManager& pSoundManager);

//    void registerShip(GraphicsElement* pGraphics);
    void registerShip(Sprite* pGraphics, Sound* pCollisionSound,
            b2Body* pBody);

    void initialize();
    void update();

    bool isDestroyed() { return mDestroyed; }

private:
    Ship(const Ship&);
    void operator=(const Ship&);

    GraphicsManager& mGraphicsManager;
    SoundManager& mSoundManager;
//    GraphicsElement* mGraphics;
    Sprite* mGraphics;
    Sound* mCollisionSound;
    b2Body* mBody;
    bool mDestroyed; int32_t mLives;
};
#endif
