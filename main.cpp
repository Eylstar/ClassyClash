#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "character.h"
#include "prop.h"
#include "wall.h"


const float globalScale = 4.0f;
const float tileSize = 16.0f * globalScale;
const int screenWidth = 15 * tileSize;
const int screenHeight = 15 * tileSize;

Texture2D mapTexture;
Texture2D skeleton, armedskeleton, vase, hole, flowerpot;
Texture2D rock1, rock2, tombstone;
Texture2D barelclosed, barelopen, bench, crate, sign;
Texture2D leftbridge, middlebridge, rightbridge;
Texture2D deadtree, fruitstree, littletree, tree;
Texture2D fenceVerticalUp, fenceVerticalMiddle, fenceVerticalBottom;

void loadAllTextures();
void placeAllDecor(std::vector<Prop> &props);
void placeAllWalls(std::vector<Wall> &walls);

int main()
{
    InitWindow(screenWidth, screenHeight, "Classy Clash");
    loadAllTextures();

    Vector2 mapPosition{};
    Vector2 staticRelativeWorldPos;

    //Character player(screenWidth, screenHeight, 30.25f * tileSize, 32.0f * tileSize);
    Character player(screenWidth, screenHeight, 8 * tileSize, 8 * tileSize);

    std::vector<Prop> props{};
    placeAllDecor(props);

    std::vector<Wall> walls{};
    placeAllWalls(walls);


    SetTargetFPS(60);
    while (!WindowShouldClose())
    {  
        BeginDrawing();
        ClearBackground({77, 138, 179, 255});
        
        staticRelativeWorldPos = player.getRelativeWorldPos();

        mapPosition = Vector2Negate(staticRelativeWorldPos);
        DrawTextureEx(mapTexture, mapPosition, 0.0f, globalScale, WHITE);

        player.inputMovement();
        player.computeMovement(GetFrameTime());
        Rectangle playerColl = player.getCollisionRec();

        for(auto &prop : props)
        {
            prop.setRenderedBool(false);
            
            if (player.getCollisionRec().y + player.getCollisionRec().height/2 >= prop.getCollisionRec(staticRelativeWorldPos).y + prop.getCollisionRec(staticRelativeWorldPos).height / 2)
            {
                prop.RenderProp(staticRelativeWorldPos);
                prop.setRenderedBool(true);
            }
            if(CheckCollisionRecs(playerColl, prop.getCollisionRec(player.getRelativeWorldPos())))
                player.addCollider(prop.getCollisionRec(player.getRelativeWorldPos()));
        }

        for (auto &wall : walls)
        {
            //DEBUG WALL COLLIDER
            //DrawRectangleRec(wall.getWallCollider(staticRelativeWorldPos), {255,0,0,70});

            if(CheckCollisionRecs(playerColl, wall.getWallCollider(player.getRelativeWorldPos())))
                player.addCollider(wall.getWallCollider(player.getRelativeWorldPos()));
                
        }
        
        player.fixMovement();
        player.updateAnimData();
        player.renderCharacter();

        //DEBUG PLAYER COLLIDER
        //DrawRectangleRec(player.getCollisionRec(), {0, 255, 0, 70});

        for(auto &prop : props)
        {
            if (!prop.getRenderedBool())
                prop.RenderProp(staticRelativeWorldPos);
            
            //DEBUG PROP COLLIDER
            //prop.RenderPropCollider(staticRelativeWorldPos);
        }
        
        
        
        EndDrawing();
    }
    
    UnloadTexture(mapTexture);
    CloseWindow();
    return 0;
}


void loadAllTextures()
{
    mapTexture = LoadTexture("textures/map/GroundMap.png");

    skeleton = LoadTexture("textures/decor/skeleton.png");
    armedskeleton = LoadTexture("textures/decor/armedskeleton.png");
    vase = LoadTexture("textures/decor/vase.png");
    hole = LoadTexture("textures/decor/hole.png");
    flowerpot = LoadTexture("textures/decor/flowerpot.png");

    rock1 = LoadTexture("textures/rocks/rock1.png");
    rock2 = LoadTexture("textures/rocks/rock2.png");
    tombstone = LoadTexture("textures/rocks/tombstone.png");

    barelclosed = LoadTexture("textures/woodenProps/barelclosed.png");
    barelopen = LoadTexture("textures/woodenProps/barelopen.png");
    bench = LoadTexture("textures/woodenProps/bench.png");
    crate = LoadTexture("textures/woodenProps/crate.png");
    sign = LoadTexture("textures/woodenProps/sign.png");
    leftbridge = LoadTexture("textures/woodenProps/leftbridge.png");
    middlebridge = LoadTexture("textures/woodenProps/middlebridge.png");
    rightbridge = LoadTexture("textures/woodenProps/rightbridge.png");

    deadtree = LoadTexture("textures/trees/deadtree.png");
    fruitstree = LoadTexture("textures/trees/fruitstree.png");
    littletree = LoadTexture("textures/trees/littletree.png");
    tree = LoadTexture("textures/trees/tree.png");

    fenceVerticalBottom = LoadTexture("textures/fences/fenceVerticalBottom.png");
    fenceVerticalMiddle = LoadTexture("textures/fences/fenceVerticalMiddle.png");
    fenceVerticalUp = LoadTexture("textures/fences/fenceVerticalUp.png");
}

void placeAllDecor(std::vector<Prop> &props)
{
    props.push_back( Prop(tree, {4, 3}, {1, 2.5}, {1, 1}, tileSize, globalScale));
    props.push_back( Prop(deadtree, {9, 3}, {0.5f, 0.5f}, {1, 1}, tileSize, globalScale));

    
    props.push_back( Prop(fenceVerticalMiddle, {4, 11}, {-100,-100}, {0,0}, tileSize, globalScale));
    props.push_back( Prop(fenceVerticalMiddle, {4, 12}, {-100,-100}, {0,0}, tileSize, globalScale));
    props.push_back( Prop(fenceVerticalMiddle, {4, 13}, {-100,-100}, {0,0}, tileSize, globalScale));
    props.push_back( Prop(fenceVerticalMiddle, {4, 14}, {-100,-100}, {0,0}, tileSize, globalScale));
    props.push_back( Prop(fenceVerticalBottom, {4, 15}, {-100,-100}, {0,0}, tileSize, globalScale));
    props.push_back( Prop(fenceVerticalUp, {4, 10}, {0.33f, 0}, {0.33f, 6}, tileSize, globalScale));

    props.push_back( Prop(rock1, {6, 7}, {0, 0.4f}, {1, 0.6f}, tileSize, globalScale));

    props.push_back( Prop(vase, {4.33f, 9}, {0.22f, 0.45f}, {0.5f, 0.45f}, tileSize, globalScale));

    props.push_back( Prop(barelclosed, {11, 9}, {0.125f, 0.5f}, {0.75f, 0.5f}, tileSize, globalScale));
    props.push_back( Prop(barelclosed, {5, 18}, {0.125f, 0.5f}, {0.75f, 0.5f}, tileSize, globalScale));
}

void placeAllWalls(std::vector<Wall> &walls)
{
    //SEA WALLS
    walls.push_back(Wall ({1, 1}, {1.8f, 40}, tileSize));
    walls.push_back(Wall ({1, 1}, {40, 1.8f}, tileSize));
    walls.push_back(Wall ({37.2, 1}, {1, 40}, tileSize));
    walls.push_back(Wall ({1, 37.2}, {40, 1}, tileSize));

    //LEFT RIVER
    walls.push_back(Wall ({24.2, 2.8}, {1, 2}, tileSize));
    walls.push_back(Wall ({25.2, 4.8}, {1, 1}, tileSize));
    walls.push_back(Wall ({26.2, 5.8}, {1, 1}, tileSize));
    walls.push_back(Wall ({26.2, 7.8}, {1, 1.5}, tileSize));
    walls.push_back(Wall ({25.2, 9.2}, {1, 2}, tileSize));
    walls.push_back(Wall ({23.2, 11.2}, {2, 2.5}, tileSize));
    walls.push_back(Wall ({21.2, 13.2}, {2, 1}, tileSize));
    walls.push_back(Wall ({20.2, 14.2}, {1, 1}, tileSize));
    walls.push_back(Wall ({19.2, 15.2}, {1, 1}, tileSize));
    walls.push_back(Wall ({18.2, 16.2}, {1, 1}, tileSize));
    walls.push_back(Wall ({17.2, 17.2}, {1, 3.5}, tileSize));
    walls.push_back(Wall ({18.2, 20.8}, {1, 6}, tileSize));
    walls.push_back(Wall ({19.2, 26.8}, {1, 3}, tileSize));
    walls.push_back(Wall ({20.2, 29.8}, {1, 4}, tileSize));
    walls.push_back(Wall ({21.2, 33.8}, {1, 2}, tileSize));
    walls.push_back(Wall ({22.2, 35.8}, {1, 1.4}, tileSize));
}
