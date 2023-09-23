#ifndef _PACKT_SHIP_HPP_
#define _PACKT_SHIP_HPP_

#include "GraphicsManager.hpp"

class Ship {
public:
    Ship(android_app* pApplication,
         GraphicsManager& pGraphicsManager);

    void registerShip(GraphicsElement* pGraphics);

    void initialize();

private:
    Ship(const Ship&);
    void operator=(const Ship&);

    GraphicsManager& mGraphicsManager;

    GraphicsElement* mGraphics;
};
#endif
