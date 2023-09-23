#ifndef _PACKT_SoundManager_HPP_
#define _PACKT_SoundManager_HPP_

#include "Types.hpp"

#include <android_native_app_glue.h>
#include <SLES/OpenSLES.h>

class SoundManager {
public:
    SoundManager(android_app* pApplication);

    status start();
    void stop();

private:
    SoundManager(const SoundManager&);
    void operator=(const SoundManager&);

    android_app* mApplication;

    // OpenSL ES engine.
    SLObjectItf mEngineObj; SLEngineItf mEngine;
    // Audio output.
    SLObjectItf mOutputMixObj;
};
#endif
