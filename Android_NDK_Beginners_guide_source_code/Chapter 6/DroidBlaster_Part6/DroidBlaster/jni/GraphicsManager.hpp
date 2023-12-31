#ifndef _PACKT_GRAPHICSMANAGER_HPP_
#define _PACKT_GRAPHICSMANAGER_HPP_

#include "Resource.hpp"
#include "Types.hpp"

#include <android_native_app_glue.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>

struct GraphicsElement {
    GraphicsElement(int32_t pWidth, int32_t pHeight):
        location(),
        width(pWidth), height(pHeight) {
    }

    Location location;
    int32_t width;  int32_t height;
};

struct TextureProperties {
    Resource* textureResource;
    GLuint texture;
    int32_t width;
    int32_t height;
};

class GraphicsManager {
public:
    GraphicsManager(android_app* pApplication);
    ~GraphicsManager();

    int32_t getRenderWidth() { return mRenderWidth; }
    int32_t getRenderHeight() { return mRenderHeight; }

    GraphicsElement* registerElement(int32_t pHeight, int32_t pWidth);

    status start();
    void stop();
    status update();

    TextureProperties* loadTexture(Resource& pResource);

private:
    GraphicsManager(const GraphicsManager&);
    void operator=(const GraphicsManager&);

    android_app* mApplication;

    int32_t mRenderWidth; int32_t mRenderHeight;
    EGLDisplay mDisplay; EGLSurface mSurface; EGLContext mContext;

    // Graphics resources.
    TextureProperties mTextures[32]; int32_t mTextureCount;

    GraphicsElement* mElements[1024]; int32_t mElementCount;
};
#endif
