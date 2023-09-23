#include "Log.hpp"
#include "SoundManager.hpp"

SoundManager::SoundManager(android_app* pApplication) :
    mApplication(pApplication),
    mEngineObj(NULL), mEngine(NULL),
    mOutputMixObj(NULL) {
    Log::info("Creating SoundManager.");
}

status SoundManager::start() {
    Log::info("Starting SoundManager.");
    SLresult result;
    const SLuint32      engineMixIIDCount = 1;
    const SLInterfaceID engineMixIIDs[]   = {SL_IID_ENGINE};
    const SLboolean     engineMixReqs[]   = {SL_BOOLEAN_TRUE};
    const SLuint32      outputMixIIDCount = 0;
    const SLInterfaceID outputMixIIDs[]   = {};
    const SLboolean     outputMixReqs[]   = {};

    // Creates OpenSL ES engine and dumps its capabilities.
    result = slCreateEngine(&mEngineObj, 0, NULL,
        engineMixIIDCount, engineMixIIDs, engineMixReqs);
    if (result != SL_RESULT_SUCCESS) goto ERROR;
    result = (*mEngineObj)->Realize(mEngineObj,SL_BOOLEAN_FALSE);
    if (result != SL_RESULT_SUCCESS) goto ERROR;
    result = (*mEngineObj)->GetInterface(mEngineObj, SL_IID_ENGINE,
        &mEngine);
    if (result != SL_RESULT_SUCCESS) goto ERROR;

    // Creates audio output.
    result = (*mEngine)->CreateOutputMix(mEngine, &mOutputMixObj,
        outputMixIIDCount, outputMixIIDs, outputMixReqs);
    result = (*mOutputMixObj)->Realize(mOutputMixObj,
        SL_BOOLEAN_FALSE);

    return STATUS_OK;

ERROR:
    Log::error("Error while starting SoundManager");
    stop();
    return STATUS_KO;
}

void SoundManager::stop() {
    Log::info("Stopping SoundManager.");

    // Destroys audio output and engine.
    if (mOutputMixObj != NULL) {
        (*mOutputMixObj)->Destroy(mOutputMixObj);
        mOutputMixObj = NULL;
    }
    if (mEngineObj != NULL) {
        (*mEngineObj)->Destroy(mEngineObj);
        mEngineObj = NULL; mEngine = NULL;
    }
}
