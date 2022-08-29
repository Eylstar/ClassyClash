#include "Character.h"
#include "raymath.h"
#include "raylib.h"
#include "stdio.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <cstdlib>

Character::Character(int winWidth, int winHeight, float initPosX, float initPosY)
{
    characterWidth = (float)texture.width / (float)maxAnimationFrames;
    characterHeight = (float)texture.height;
    screenPos = {
        (float)winWidth / 2.0f - scale * (0.5f * characterWidth),
        (float)winHeight / 2.0f - scale * (0.5f * characterHeight)
    };
    worldPos = {initPosX, initPosY};
}

void Character::inputMovement()
{
    worldPosLastFrame = worldPos;
    direction = {0.0f, 0.0f};
    if (IsKeyDown(KEY_A)) direction.x -= 1.0f;
    if (IsKeyDown(KEY_D)) direction.x += 1.0f;
    if (IsKeyDown(KEY_W)) direction.y -= 1.0f;
    if (IsKeyDown(KEY_S)) direction.y += 1.0f;
    initDirection = direction;
}

void Character::computeMovement(float DT)
{
    colls.clear();
    deltaTime = DT;
    if (Vector2Length(direction) != 0.0f)
    {
        direction.x < 0.0f ? rightLeft = -1.0f : rightLeft = 1.0f;
        direction = Vector2Scale(Vector2Normalize(direction), characterSpeed);
        worldPos = Vector2Add(worldPos, direction);
        texture = runTexture;
    }
    else
        texture = idleTexture;
}

void Character::updateAnimData()
{
    elapsedTime += deltaTime;
    if (elapsedTime >= updateAnimFrequency)
    {
        animationFrame++;
        elapsedTime = 0.0f;
        if (animationFrame >= maxAnimationFrames) animationFrame = 0;
    }
}

void Character::addCollider(Rectangle coll) {colls.push_back(coll);}

void Character::fixMovement()
{
    if (colls.size() == 0) return;
    else if (colls.size() == 1 && (direction.x == 0 || direction.y == 0))
    {
        undoMovement();
        return;
    }

    Rectangle playerColl = getCollisionRec();
    for (auto coll : colls)
    {
        if ((playerColl.x + playerColl.width > coll.x || playerColl.x < coll.x + coll.width))
        {
            if (playerColl.y > coll.y && coll.y + coll.height > playerColl.y && playerColl.y + playerColl.height > coll.y + coll.height)
            {
                if (initDirection.y < 0)
                {
                        direction.y = 0;
                }
            }
            else if (playerColl.y < coll.y && coll.y < playerColl.y + playerColl.height)
            {
                if (initDirection.y > 0) 
                {
                        direction.y = 0;
                }
            }
        }
        if ((playerColl.y + playerColl.height > coll.y || playerColl.y < coll.y + coll.height))
        {
            if (playerColl.x > coll.x && coll.x + coll.width > playerColl.x && playerColl.x + playerColl.width > coll.x + coll.width)
            {
                if (initDirection.x < 0)
                {
                        direction.x = 0;
                }
            }
            else if (playerColl.x < coll.x && playerColl.x + playerColl.width > coll.x)
            {
                if (initDirection.x > 0) 
                {
                        direction.x = 0;
                }
            }
        }
    }

    undoMovement();
    worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), characterSpeed));
}

void Character::renderCharacter()
{
    Rectangle source = {characterWidth * animationFrame, 0.0f, rightLeft * characterWidth, characterHeight};
    Rectangle destination = {screenPos.x, screenPos.y, scale * characterWidth, scale * characterHeight};
    DrawTexturePro(texture, source, destination, {0.0f, 0.0f}, 0.0f, WHITE);
}

void Character::undoMovement() {worldPos = worldPosLastFrame;}

Rectangle Character::getCollisionRec()
{
    return Rectangle{
        screenPos.x + ((characterWidth / 3.0f) * scale) / 2.0f,
        screenPos.y + (characterHeight /3.0f) *2.3f *scale,
        characterWidth * scale - ((characterWidth / 3.0f) * scale),
        (characterHeight * scale) / 6.0f
    };
}