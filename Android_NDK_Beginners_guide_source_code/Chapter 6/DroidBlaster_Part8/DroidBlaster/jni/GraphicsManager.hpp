#ifndef _PACKT_GRAPHICSMANAGER_HPP_
#define _PACKT_GRAPHICSMANAGER_HPP_

#include "Resource.hpp"
#include "Types.hpp"

#include <android_native_app_glue.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>

//struct GraphicsElement {
//    GraphicsElement(int32_t pWidth, int32_t pHeight):
//        location(),
//        width(pWidth), height(pHeight) {
//    }
//
//    Location location;
//    int32_t width;  int32_t height;
//};

class GraphicsComponent {
public:
    virtual status load() = 0;
    virtual void draw() = 0;
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
    GLfloat* getProjectionMatrix() { return mProjectionMatrix[0]; }

//    GraphicsElement* registerElement(int32_t pHeight, int32_t pWidth);
    void registerComponent(GraphicsComponent* pComponent);

    status start();
    void stop();
    status update();

    TextureProperties* loadTexture(Resource& pResource);
    GLuint loadShader(const char* pVertexShader,
            const char* pFragmentShader);
    GLuint loadVertexBuffer(const void* pVertexBuffer,
            int32_t pVertexBufferSize);

private:
    GraphicsManager(const GraphicsManager&);
    void operator=(const GraphicsManager&);

    android_app* mApplication;

    int32_t mRenderWidth; int32_t mRenderHeight;
    EGLDisplay mDisplay; EGLSurface mSurface; EGLContext mContext;
    GLfloat mProjectionMatrix[4][4];

    // Graphics resources.
    TextureProperties mTextures[32]; int32_t mTextureCount;
    GLuint mShaders[32]; int32_t mShaderCount;
    GLuint mVertexBuffers[32]; int32_t mVertexBufferCount;

//    GraphicsElement* mElements[1024]; int32_t mElementCount;
    GraphicsComponent* mComponents[32]; int32_t mComponentCount;
};
#endif
