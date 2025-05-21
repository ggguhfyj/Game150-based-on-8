#include "Mode7.h"

//https://www.youtube.com/watch?v=0kVM6dJeWaY

float Mode7::GetPlayerX()
{
    return fWorldX;
}

float Mode7::GetPlayerY()
{
    return fWorldY;
}

void Mode7::DrawMode7Line(int y)
{
    float fSampleDepth = (float)y / (windowsize.y / 2.0f);

    float fStartX = (frustum.Far1.x - frustum.Near1.x) / (fSampleDepth)+frustum.Near1.x;
    float fStartY = (frustum.Far1.y - frustum.Near1.y) / (fSampleDepth)+frustum.Near1.y;
    float fEndX = (frustum.Far2.x - frustum.Near2.x) / (fSampleDepth)+frustum.Near2.x;
    float fEndY = (frustum.Far2.y - frustum.Near2.y) / (fSampleDepth)+frustum.Near2.y;

    for (int x = 0; x < windowsize.x; x++) {
        float fSampleWidth = (float)x / windowsize.x;
        float fSampleX = (fEndX - fStartX) * fSampleWidth + fStartX;
        float fSampleY = (fEndY - fStartY) * fSampleWidth + fStartY;

        int texX = ((int)fSampleX % texMap.width + texMap.width) % texMap.width;
        int texY = ((int)fSampleY % texMap.height + texMap.height) % texMap.height;

        Color color = GetImageColor(imgMap, texX, texY);
        DrawPixel(x + (int)position.x, (int)position.y + (int)windowsize.y / 2 + y, color);

        
        
    }
  /*  for (Vector2 tl : TestMap::trafficlight)
    {
        if (tl.x == texX && tl.y == texY)
        {
            DrawTexture(trafficlightsTex, x + (int)position.x, (int)position.y + (int)windowsize.y/2 + y, WHITE);
        }
        fo
    }*/

    //DrawTextureNPatch(Texture2D texture, NPatchInfo nPatchInfo, Rectangle dest, Vector2 origin, float rotation, Color tint);
}

void Mode7::RepositionWindow()
{
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        if (GetMousePosition().x > position.x && GetMousePosition().x < (position.x + windowsize.x))
            if (GetMousePosition().y > position.y-tabheight && GetMousePosition().y < (position.y + windowsize.y))
            {
                position.x += GetMouseDelta().x;
                position.y += GetMouseDelta().y;
            }
    }
}

void Mode7::ReSizeWindow()
{
    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
    {
        if (GetMousePosition().x > position.x && GetMousePosition().x < (position.x + windowsize.x))
            if (GetMousePosition().y > position.y - tabheight && GetMousePosition().y < (position.y + windowsize.y))
            {
                windowsize.x += GetMouseDelta().x;
                windowsize.y += GetMouseDelta().y;
            }
    }
}

void Mode7::Load()
{
    texSky = LoadTexture("Assets/sky1.png");
    texMap = LoadTexture("CreatedMap.png");
    windowtabs = LoadTexture("Assets/windowtabs.png");
    trafficlightsTex = LoadTexture("Assets/traffic-light.png");
    imgMap = LoadImageFromTexture(texMap);
    
}

void Mode7::Update()
{
    player.Update(fSpeed, GetFrameTime());

    if (IsKeyDown(KEY_Q)) fNear += 0.5f * fSpeed * GetFrameTime();

    if (IsKeyDown(KEY_A)) fNear -= 0.5f * fSpeed * GetFrameTime();

    if (IsKeyDown(KEY_W)) fFar += 0.5f * fSpeed * GetFrameTime();

    if (IsKeyDown(KEY_S)) fFar -= 0.5f * fSpeed * GetFrameTime();




    if (IsKeyDown(KEY_Z)) fFoVHalf += 0.1f * GetFrameTime();

    if (IsKeyDown(KEY_X)) fFoVHalf -= 0.1f * GetFrameTime();

    if (IsKeyDown(KEY_RIGHT)) {
        fWorldA += 1.0f * GetFrameTime();
        skyOffset += 1.0f * fSpeed * 1.5f * GetFrameTime();
        if (player.fuel <= 0.0f && fSpeed <= 0.0f) {
            fWorldA = 0;
            skyOffset = 0;
        }
    }
    if (IsKeyDown(KEY_LEFT)) {
        fWorldA -= 1.0f * GetFrameTime();
        skyOffset -= 1.0f * fSpeed * 1.5f * GetFrameTime();
        if (player.fuel <= 0.0f && fSpeed <= 0.0f) {
            fWorldA = 0;
            skyOffset = 0;
        }
    }
    if (player.fuel <= 0.0f) {
        fSpeed -= 3;
        if (fSpeed < 0) fSpeed = 0;

    }
    if (IsKeyDown(KEY_UP)) {

        if (IsKeyDown(KEY_LEFT_SHIFT))
        {
            if (fSpeed < fMaxSpeed)
                fSpeed += 3;
        }
        fSpeed++;
    }
    else
    {
        if (fabs(fSpeed) < 5)fSpeed = 0;
        if (fSpeed > 0)
            fSpeed -= 3;

    }

    if (IsKeyDown(KEY_DOWN)) {
        /* fWorldX -= cosf(fWorldA) * fSpeed * GetFrameTime();
         fWorldY -= sinf(fWorldA) * fSpeed * GetFrameTime();*/

        if (fSpeed > 0) {
            fSpeed -= 5 * GetFrameTime();
            if (fSpeed < 0) fSpeed = 0;
        }
    }

    fWorldX += cosf(fWorldA) * fSpeed * GetFrameTime();
    fWorldY += sinf(fWorldA) * fSpeed * GetFrameTime();

    player.Update(fSpeed, GetFrameTime());

    frustum.Far1.x = fWorldX + cosf(fWorldA - fFoVHalf) * fFar;
    frustum.Far1.y = fWorldY + sinf(fWorldA - fFoVHalf) * fFar;

    frustum.Near1.x = fWorldX + cosf(fWorldA - fFoVHalf) * fNear;
    frustum.Near1.y = fWorldY + sinf(fWorldA - fFoVHalf) * fNear;

    frustum.Far2.x = fWorldX + cosf(fWorldA + fFoVHalf) * fFar;
    frustum.Far2.y = fWorldY + sinf(fWorldA + fFoVHalf) * fFar;

    frustum.Near2.x = fWorldX + cosf(fWorldA + fFoVHalf) * fNear;
    frustum.Near2.y = fWorldY + sinf(fWorldA + fFoVHalf) * fNear;

    skyOffset = (float)fmod(skyOffset, texSky.width);


    coll_check = false;
    Vector2 player_position = { fWorldX, fWorldY };
    if (player_position.x > 0 && player_position.y > 0) {
        std::vector<Vector2> circleCenters;
        float startX = 1500;
        float startY = 750;
        float radius = 100;

        for (int row = 0; row < 10; ++row) {
            for (int i = 0; i <= row; ++i) {
                float cx = startX + (i * 300) - (row * 150);    // Same row: X += 300
                float cy = startY + (row * 150);                // Down-left: X -= 150, Y += 150
                circleCenters.push_back({ cx, cy });            // Down-right: X += 150, Y += 150
            }
        }

        for (Vector2 center : circleCenters) {
            if (CheckCollisionPointCircle(player_position, center, radius)) {
                coll_check = true;
                break;
            }
        }
    }
    
}

void Mode7::Draw()
{
   
    RepositionWindow();
    ReSizeWindow();

    Rectangle skySource = { skyOffset, 0, (float)texSky.width, (float)texSky.height };
    Rectangle skyDest = { position.x, position.y, windowsize.x, windowsize.y/2 };
    DrawTexturePro(texSky, skySource, skyDest, { 0, 0 }, 0.0f, WHITE);

    

    for (int y = 0; y < windowsize.y / 2; y++) {
        DrawMode7Line(y);
    }

    Mode7::player.Update(Mode7::fSpeed, GetFrameTime());
    DrawRectangle((int)position.x, (int)position.y-tabheight, (int)windowsize.x, tabheight, GRAY);
    DrawRectangle((int)position.x+5, (int)position.y - tabheight + 5, (int)windowsize.x-10, tabheight-10, BLUE);
    DrawTexture(windowtabs, (int)position.x + 10, (int)position.y - tabheight +10, WHITE);
    DrawLine((int)position.x, (int)position.y+(int)windowsize.y / 2, (int)position.x+(int)windowsize.x, (int)position.y + (int)windowsize.y / 2, BLUE);
    DrawFPS((int)position.x, (int)position.y + (int)windowsize.y / 2 - 20);
    DrawText("ARROWKEYS TO MOVE, \n Q,A,W,S to change camera settings", (int)position.x, (int)position.y , 25, GREEN);
    

    for (int y = 0; y < windowsize.y / 2; y++) {
        DrawMode7Line(y);
    }

    DrawText(TextFormat("Position: (%.1f, %.1f)", fWorldX, fWorldY),
        (int)(position.x + windowsize.x - 300),
        (int)(position.y + 30),
        20,
        YELLOW);

    
    Vector2 fuelBarPos = { position.x + 20, position.y + windowsize.y - 40 };
    player.DrawFuelBar(fuelBarPos);

    if (coll_check == true) {
        DrawText(TextFormat("player in the cirle"),
            (int)(position.x + windowsize.x - 300),
            (int)(position.y + 60),
            20,
            YELLOW);
    }
}

void Mode7::unload()
{
    UnloadTexture(texSky);
    UnloadTexture(texMap);
    UnloadImage(imgMap);
}




