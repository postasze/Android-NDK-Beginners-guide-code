#ifndef _PACKT_GRAPHICSSPRITEBATCH_HPP_
#define _PACKT_GRAPHICSSPRITEBATCH_HPP_

#include "GraphicsManager.hpp"
#include "Sprite.hpp"
#include "TimeManager.hpp"
#include "Types.hpp"

#include <GLES2/gl2.h>

class SpriteBatch : public GraphicsComponent {
public:
    SpriteBatch(TimeManager& pTimeManager,
            GraphicsManager& pGraphicsManager);
    ~SpriteBatch();

    Sprite* registerSprite(Resource& pTextureResource,
        int32_t pHeight, int32_t pWidth);

    status load();
    void draw();

private:
    SpriteBatch(const SpriteBatch&);
    void operator=(const SpriteBatch&);

    TimeManager& mTimeManager;
    GraphicsManager& mGraphicsManager;

    Sprite* mSprites[1024]; int32_t mSpriteCount;
    Sprite::Vertex mVertices[1024]; int32_t mVertexCount;
    GLushort mIndexes[1024]; int32_t mIndexCount;
    GLuint mShaderProgram;
    GLuint aPosition; GLuint aTexture;
    GLuint uProjection; GLuint uTexture;
};
#endif
