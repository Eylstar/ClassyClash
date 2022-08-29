#pragma once
#include "raylib.h"
#include "Prop.h"
#include "wall.h"
#include <vector>

class Character 
{
public:
    Character(int winWidth, int winHeight, float initPosX, float initPosY);

    inline Vector2 getRelativeWorldPos() {return {worldPos.x - screenPos.x, worldPos.y - screenPos.y};}

    void inputMovement();
    void computeMovement(float deltaTime);
    void updateAnimData();
    void renderCharacter();

    void addCollider(Rectangle collider);
    void fixMovement();

    void undoMovement();
    Rectangle getCollisionRec();


private:
    Texture2D texture = LoadTexture("sprites/characters/playerIdle.png");
    Texture2D idleTexture = LoadTexture("sprites/characters/playerIdle.png");
    Texture2D runTexture = LoadTexture("sprites/characters/playerWalk.png");

    Vector2 screenPos{};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    Vector2 direction{};
    Vector2 initDirection{};

    float characterWidth{};
    float characterHeight{};

    std::vector<Rectangle> colls{};

    float deltaTime{};
    float rightLeft = 1.0f;
    float elapsedTime = 0.0f;
    int animationFrame = 0;
    int maxAnimationFrames = 6;
    float updateAnimFrequency = 1.0f/12.0f;
    //float characterSpeed = 10.0f;
    float characterSpeed = 5.0f;

    float scale = 4.0f;
};