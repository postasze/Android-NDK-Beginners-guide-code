#ifndef _PACKT_STARFIELD_HPP_
#define _PACKT_STARFIELD_HPP_

#include "GraphicsManager.hpp"
#include "TimeManager.hpp"
#include "Types.hpp"

#include <GLES2/gl2.h>

class StarField : public GraphicsComponent {
public:
    StarField(android_app* pApplication, TimeManager& pTimeManager,
            GraphicsManager& pGraphicsManager, int32_t pStarCount,
            Resource& pTextureResource);

    status load();
    void draw();

private:
    StarField(const StarField&);
    void operator=(const StarField&);

    struct Vertex {
        GLfloat x, y, z;
    };

    TimeManager& mTimeManager;
    GraphicsManager& mGraphicsManager;

    int32_t mStarCount;
    Resource& mTextureResource;

    GLuint mVertexBuffer; GLuint mTexture; GLuint mShaderProgram;
    GLuint aPosition; GLuint uProjection;
    GLuint uTime; GLuint uHeight; GLuint uTexture;
};
#endif
