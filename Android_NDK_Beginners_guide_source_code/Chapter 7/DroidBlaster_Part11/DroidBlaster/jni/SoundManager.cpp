#include "Log.hpp"
#include "Resource.hpp"
#include "SoundManager.hpp"

SoundManager::SoundManager(android_app* pApplication) :
    mApplication(pApplication),
    mEngineObj(NULL), mEngine(NULL),
    mOutputMixObj(NULL),
    mBGMPlayerObj(NULL), mBGMPlayer(NULL), mBGMPlayerSeek(NULL) {
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

    // Stops and destroys BGM player.
    stopBGM();

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

status SoundManager::playBGM(const char* pPath) {
    SLresult result;
    Log::info("Opening BGM %s", pPath);

    // Set-up BGM audio source.
    Resource resource(mApplication, pPath);
    ResourceDescriptor descriptor = resource.descriptor();
    if (descriptor.mDescriptor < 0) {
        Log::info("Could not open BGM file");
        return STATUS_KO;
    }

    SLDataLocator_AndroidFD dataLocatorIn;
    dataLocatorIn.locatorType = SL_DATALOCATOR_ANDROIDFD;
    dataLocatorIn.fd          = descriptor.mDescriptor;
    dataLocatorIn.offset      = descriptor.mStart;
    dataLocatorIn.length      = descriptor.mLength;

    SLDataFormat_MIME dataFormat;
    dataFormat.formatType    = SL_DATAFORMAT_MIME;
    dataFormat.mimeType      = NULL;
    dataFormat.containerType = SL_CONTAINERTYPE_UNSPECIFIED;

    SLDataSource dataSource;
    dataSource.pLocator = &dataLocatorIn;
    dataSource.pFormat  = &dataFormat;

    SLDataLocator_OutputMix dataLocatorOut;
    dataLocatorOut.locatorType = SL_DATALOCATOR_OUTPUTMIX;
    dataLocatorOut.outputMix   = mOutputMixObj;

    SLDataSink dataSink;
    dataSink.pLocator = &dataLocatorOut;
    dataSink.pFormat  = NULL;

    // Creates BGM player and retrieves its interfaces.
    const SLuint32 bgmPlayerIIDCount = 2;
    const SLInterfaceID bgmPlayerIIDs[] =
        { SL_IID_PLAY, SL_IID_SEEK };
    const SLboolean bgmPlayerReqs[] =
        { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };

    result = (*mEngine)->CreateAudioPlayer(mEngine,
        &mBGMPlayerObj, &dataSource, &dataSink,
        bgmPlayerIIDCount, bgmPlayerIIDs, bgmPlayerReqs);
    if (result != SL_RESULT_SUCCESS) goto ERROR;
    result = (*mBGMPlayerObj)->Realize(mBGMPlayerObj,
        SL_BOOLEAN_FALSE);
    if (result != SL_RESULT_SUCCESS) goto ERROR;

    result = (*mBGMPlayerObj)->GetInterface(mBGMPlayerObj,
        SL_IID_PLAY, &mBGMPlayer);
    if (result != SL_RESULT_SUCCESS) goto ERROR;
    result = (*mBGMPlayerObj)->GetInterface(mBGMPlayerObj,
        SL_IID_SEEK, &mBGMPlayerSeek);
    if (result != SL_RESULT_SUCCESS) goto ERROR;

    // Enables looping and starts playing.
    result = (*mBGMPlayerSeek)->SetLoop(mBGMPlayerSeek,
        SL_BOOLEAN_TRUE, 0, SL_TIME_UNKNOWN);
    if (result != SL_RESULT_SUCCESS) goto ERROR;
    result = (*mBGMPlayer)->SetPlayState(mBGMPlayer,
        SL_PLAYSTATE_PLAYING);
    if (result != SL_RESULT_SUCCESS) goto ERROR;

    return STATUS_OK;

ERROR:
    Log::error("Error playing BGM");
    return STATUS_KO;
}

void SoundManager::stopBGM() {
    if (mBGMPlayer != NULL) {
        SLuint32 bgmPlayerState;
        (*mBGMPlayerObj)->GetState(mBGMPlayerObj,
            &bgmPlayerState);
        if (bgmPlayerState == SL_OBJECT_STATE_REALIZED) {
            (*mBGMPlayer)->SetPlayState(mBGMPlayer,
                SL_PLAYSTATE_PAUSED);

            (*mBGMPlayerObj)->Destroy(mBGMPlayerObj);
            mBGMPlayerObj = NULL;
            mBGMPlayer = NULL; mBGMPlayerSeek = NULL;
        }
    }
}
