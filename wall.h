#pragma once
#include "raylib.h"

class Wall
{
public:

    Wall(Vector2 pos, Vector2 collScale, float tileSize);
    Rectangle getWallCollider(Vector2 playerPos);

private:

    Vector2 worldPos{};
    Vector2 colliderScale{};
    float tileScale{};
};