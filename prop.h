#pragma once
#include "raylib.h"

class Prop
{
public:
    Prop(Texture2D tex, Vector2 pos, Vector2 collOff, Vector2 collScale, float tileSize, float globScale);

    inline void setRenderedBool(bool rend){rendered = rend;}
    inline bool getRenderedBool(){return rendered;}

    void RenderProp(Vector2 playerPos);
    void RenderPropCollider(Vector2 playerPos);
    Rectangle getCollisionRec(Vector2 playerPos);     

private:
    Texture2D propTexture{};
    Vector2 worldPos{};

    Vector2 collierOffset{};
    Vector2 colliderScale{};

    float tileScale{};
    float globalScale{};

    bool rendered{};
};