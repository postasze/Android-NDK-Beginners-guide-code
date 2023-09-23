#ifndef _PACKT_MOVEABLEBODY_HPP_
#define _PACKT_MOVEABLEBODY_HPP_

#include "InputManager.hpp"
#include "PhysicsManager.hpp"
#include "Types.hpp"

class MoveableBody {
public:
    MoveableBody(android_app* pApplication,
       InputManager& pInputManager, PhysicsManager& pPhysicsManager);

    PhysicsBody* registerMoveableBody(Location& pLocation,
            int32_t pSizeX, int32_t pSizeY);

    void initialize();
    void update();

private:
    MoveableBody(const MoveableBody&);
    void operator=(const MoveableBody&);

    PhysicsManager& mPhysicsManager;
    InputManager& mInputManager;

    PhysicsBody* mBody;
};
#endif
