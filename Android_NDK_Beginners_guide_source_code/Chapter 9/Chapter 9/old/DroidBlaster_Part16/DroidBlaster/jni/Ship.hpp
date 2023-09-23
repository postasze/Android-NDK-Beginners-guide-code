#ifndef _PACKT_SHIP_HPP_
#define _PACKT_SHIP_HPP_

#include "GraphicsManager.hpp"
#include "Sprite.hpp"
#include "SoundManager.hpp"
#include "Sound.hpp"

class Ship {
public:
    Ship(android_app* pApplication,
         GraphicsManager& pGraphicsManager,
         SoundManager& pSoundManager);

//    void registerShip(GraphicsElement* pGraphics);
    void registerShip(Sprite* pGraphics, Sound* pCollisionSound);

    void initialize();

private:
    Ship(const Ship&);
    void operator=(const Ship&);

    GraphicsManager& mGraphicsManager;
    SoundManager& mSoundManager;
//    GraphicsElement* mGraphics;
    Sprite* mGraphics;
    Sound* mCollisionSound;
};
#endif
