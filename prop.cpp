#include "prop.h"
#include "raymath.h"

Prop::Prop(Texture2D tex, Vector2 pos, Vector2 collOff, Vector2 collScale, float tileSize, float globScale) : 
    propTexture(tex), 
    worldPos(Vector2Scale(pos, tileSize)), 
    collierOffset(collOff),
    colliderScale(collScale),
    tileScale(tileSize),
    globalScale(globScale)
    {
    }


Rectangle Prop::getCollisionRec(Vector2 playerPos)
{
    Vector2 screenPos = Vector2Subtract(worldPos , playerPos);
    return Rectangle {
        screenPos.x + collierOffset.x * tileScale,
        screenPos.y + collierOffset.y * tileScale,
        colliderScale.x * tileScale, 
        colliderScale.y * tileScale
    };
}


void Prop::RenderProp(Vector2 playerPos)
{
    Vector2 screenPos = Vector2Subtract(worldPos , playerPos);
    DrawTextureEx(propTexture, screenPos, 0.0f, globalScale, WHITE);
}

void Prop::RenderPropCollider(Vector2 playerPos)
{
    DrawRectangleRec(getCollisionRec(playerPos), {255, 0, 0, 70});
}
