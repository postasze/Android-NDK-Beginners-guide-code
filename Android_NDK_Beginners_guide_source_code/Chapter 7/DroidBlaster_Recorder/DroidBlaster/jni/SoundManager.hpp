#ifndef _PACKT_SoundManager_HPP_
#define _PACKT_SoundManager_HPP_

#include "Sound.hpp"
#include "SoundQueue.hpp"
#include "Types.hpp"

#include <android_native_app_glue.h>
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

class SoundManager {
public:
    SoundManager(android_app* pApplication);
    ~SoundManager();

    status start();
    void stop();

    status playBGM(Resource& pResource);
    void stopBGM();

    Sound* registerSound(Resource& pResource);
    void playSound(Sound* pSound);

    void recordSound();
    void playRecordedSound();

private:
    SoundManager(const SoundManager&);
    void operator=(const SoundManager&);
    status startSoundRecorder();
    static void callback_recorder(
        SLAndroidSimpleBufferQueueItf pQueue, void* pContext);

    android_app* mApplication;

    // OpenSL ES engine.
    SLObjectItf mEngineObj; SLEngineItf mEngine;
    // Audio output.
    SLObjectItf mOutputMixObj;

    // Background music player.
    SLObjectItf mBGMPlayerObj; SLPlayItf mBGMPlayer;
    SLSeekItf mBGMPlayerSeek;

    // Sound players.
    static const int32_t QUEUE_COUNT = 5;
    SoundQueue mSoundQueues[QUEUE_COUNT]; int32_t mCurrentQueue;
    // Sounds.
    Sound* mSounds[32]; int32_t mSoundCount;

    // Sound recorder.
    SLObjectItf mRecorderObj; SLRecordItf mRecorder;
    SLAndroidSimpleBufferQueueItf mRecorderQueue;
    // Record buffer.
    Sound mRecordedSound;
};
#endif
