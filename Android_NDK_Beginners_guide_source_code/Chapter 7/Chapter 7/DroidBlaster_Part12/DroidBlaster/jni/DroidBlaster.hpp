#ifndef _PACKT_DROIDBLASTER_HPP_
#define _PACKT_DROIDBLASTER_HPP_

#include "ActivityHandler.hpp"
#include "Asteroid.hpp"
#include "EventLoop.hpp"
#include "GraphicsManager.hpp"
#include "PhysicsManager.hpp"
#include "Resource.hpp"
#include "Ship.hpp"
#include "SoundManager.hpp"
#include "SpriteBatch.hpp"
#include "StarField.hpp"
#include "TimeManager.hpp"
#include "Types.hpp"

class DroidBlaster : public ActivityHandler {
public:
    DroidBlaster(android_app* pApplication);
    void run();

protected:
    status onActivate();
    void onDeactivate();
    status onStep();

    void onStart();
    void onResume();
    void onPause();
    void onStop();
    void onDestroy();

    void onSaveInstanceState(void** pData, size_t* pSize);
    void onConfigurationChanged();
    void onLowMemory();

    void onCreateWindow();
    void onDestroyWindow();
    void onGainFocus();
    void onLostFocus();

private:
    DroidBlaster(const DroidBlaster&);
    void operator=(const DroidBlaster&);

    TimeManager     mTimeManager;
    GraphicsManager mGraphicsManager;
    PhysicsManager  mPhysicsManager;
    SoundManager    mSoundManager;
    EventLoop mEventLoop;

    Resource mAsteroidTexture;
    Resource mShipTexture;
    Resource mStarTexture;
    Resource mBGM;
    Resource mCollisionSound;

    Asteroid mAsteroids;
    Ship mShip;
    StarField mStarField;
    SpriteBatch mSpriteBatch;
};
#endif
