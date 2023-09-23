#ifndef _PACKT_SOUNDQUEUE_HPP_
#define _PACKT_SOUNDQUEUE_HPP_

#include "Sound.hpp"

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

class SoundQueue {
public:
    SoundQueue();

    status initialize(SLEngineItf pEngine, SLObjectItf pOutputMixObj);
    void finalize();
    void playSound(Sound* pSound);

private:
    SoundQueue(const SoundQueue&);
    void operator=(const SoundQueue&);

    // Sound player.
    SLObjectItf mPlayerObj; SLPlayItf mPlayer;
    SLBufferQueueItf mPlayerQueue;
};
#endif
