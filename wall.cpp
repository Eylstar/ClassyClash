#include "wall.h"
#include "raymath.h"


Wall::Wall(Vector2 pos, Vector2 collScale, float tileSize) : 
    worldPos(Vector2Scale(pos, tileSize)), 
    colliderScale(collScale), 
    tileScale(tileSize)
{}

Rectangle Wall::getWallCollider(Vector2 playerPos)
{
    Vector2 screenPos = Vector2Subtract(worldPos, playerPos);
    return Rectangle{
        screenPos.x,
        screenPos.y, 
        colliderScale.x * tileScale, 
        colliderScale.y * tileScale
    };
}