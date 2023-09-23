#include "GraphicsManager.hpp"
#include "Log.hpp"

GraphicsManager::GraphicsManager(android_app* pApplication) :
    mApplication(pApplication),
    mRenderWidth(0), mRenderHeight(0),
    mElements(), mElementCount(0) {
    Log::info("Creating GraphicsManager.");
}

GraphicsManager::~GraphicsManager() {
    Log::info("Destroying GraphicsManager.");
    for (int32_t i = 0; i < mElementCount; ++i) {
        delete mElements[i];
    }
}

GraphicsElement* GraphicsManager::registerElement(int32_t pHeight,
        int32_t pWidth) {
    mElements[mElementCount] = new GraphicsElement(pHeight, pWidth);
    return mElements[mElementCount++];
}

status GraphicsManager::start() {
    Log::info("Starting GraphicsManager.");

    // Forces 32 bits format.
    ANativeWindow_Buffer windowBuffer;
    if (ANativeWindow_setBuffersGeometry(mApplication->window, 0, 0,
        WINDOW_FORMAT_RGBX_8888) < 0) {
        Log::error("Error while setting buffer geometry.");
        return STATUS_KO;
    }

    // Needs to lock the window buffer to get its properties.
    if (ANativeWindow_lock(mApplication->window,
            &windowBuffer, NULL) >= 0) {
        mRenderWidth = windowBuffer.width;
        mRenderHeight = windowBuffer.height;
        ANativeWindow_unlockAndPost(mApplication->window);
    } else {
        Log::error("Error while locking window.");
        return STATUS_KO;
    }
    return STATUS_OK;
}

status GraphicsManager::update() {
    // Locks the window buffer and draws on it.
    ANativeWindow_Buffer windowBuffer;
    if (ANativeWindow_lock(mApplication->window,
            &windowBuffer, NULL) < 0) {
        Log::error("Error while starting GraphicsManager");
        return STATUS_KO;
    }

    // Clears the window.
    memset(windowBuffer.bits, 0, windowBuffer.stride *
            windowBuffer.height * sizeof(uint32_t*));

    // Renders graphic elements.
    int32_t maxX = windowBuffer.width - 1;
    int32_t maxY = windowBuffer.height - 1;
    for (int32_t i = 0; i < mElementCount; ++i) {
        GraphicsElement* element = mElements[i];

        // Computes coordinates.
        int32_t leftX = element->location.x - element->width / 2;
        int32_t rightX = element->location.x + element->width / 2;
        int32_t leftY = windowBuffer.height - element->location.y
                            - element->height / 2;
        int32_t rightY = windowBuffer.height - element->location.y
                            + element->height / 2;

        // Clips coordinates.
        if (rightX < 0 || leftX > maxX
         || rightY < 0 || leftY > maxY) continue;

        if (leftX < 0) leftX = 0;
        else if (rightX > maxX) rightX = maxX;
        if (leftY < 0) leftY = 0;
        else if (rightY > maxY) rightY = maxY;

        // Draws a rectangle.
        uint32_t* line = (uint32_t*) (windowBuffer.bits)
                        + (windowBuffer.stride * leftY);
        for (int iY = leftY; iY <= rightY; iY++) {
            for (int iX = leftX; iX <= rightX; iX++) {
                line[iX] = 0X000000FF; // Red color
            }
            line = line + windowBuffer.stride;
        }
    }

    // Finshed drawing.
    ANativeWindow_unlockAndPost(mApplication->window);
    return STATUS_OK;
}
