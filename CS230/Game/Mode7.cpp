#include "Mode7.h"

//https://www.youtube.com/watch?v=0kVM6dJeWaY

void Mode7::DrawMode7Line(int y) //y doesnt skip
{
    float fSampleDepth = (float) y / (windowsize.y / 2.0f); 

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
        DrawRectangle((int)position.x + x * blowup_scale, (int)position.y + blowup_scale * ((int)windowsize.y / 2 + y), blowup_scale, blowup_scale, color);
        /*for (Vector2 tl : TestMap::trafficlight)
        {
            if ((int)tl.x == texX && (int)tl.y == texY)
            {
                DrawTexture(trafficlightsTex, (int)position.x + (x * blowup_scale), (int)position.y + (blowup_scale * ((int)windowsize.y / 2 + y) - 50), WHITE);
            }
        }
        */
        //if (trafficlight_set.contains(vec2{ texX,texY }))/ unordered map 
        //{
        //    DrawTexture(trafficlightsTex, (int)position.x + x * blowup_scale, (int)position.y + blowup_scale * ((int)windowsize.y / 2 + y) - 20, WHITE);
        //}
        
        
    }
    

    
}
void Mode7::Load()
{
    texSky = LoadTexture("Assets/Sky.png");

    texMap = LoadTexture("Assets/snow texture.png");
    windowtabs = LoadTexture("Assets/windowtabs.png");
    trafficlightsTex = LoadTexture("Assets/traffic-light.png");

    player[0] = LoadTexture("Assets/Player/PlayerLeft-1.png");
    player[1] = LoadTexture("Assets/Player/PlayerLeft-2.png");
    player[2] = LoadTexture("Assets/Player/PlayerLeft-3.png");

    player[3] = LoadTexture("Assets/Player/PlayerRight-1.png");
    player[4] = LoadTexture("Assets/Player/PlayerRight-2.png");
    player[5] = LoadTexture("Assets/Player/PlayerRight-3.png");
    imgMap = LoadImageFromTexture(texMap);
}
void Mode7::Update()
{
    if (IsKeyDown(KEY_Q)) fNear +=10 * GetFrameTime();

    if (IsKeyDown(KEY_A)) fNear -= 10* GetFrameTime();

    if (IsKeyDown(KEY_W)) fFar += 10* GetFrameTime();       

    if (IsKeyDown(KEY_S)) fFar -= 10* GetFrameTime();

    if (IsKeyDown(KEY_Z)) fFoVHalf += 0.1f * GetFrameTime();

    if (IsKeyDown(KEY_X)) fFoVHalf -= 0.1f * GetFrameTime();

    if (IsKeyDown(KEY_RIGHT)) {
        right = true;
    }
    if (IsKeyDown(KEY_LEFT)) {
        right = false;
    }
    if (right) {
        fWorldA += 2.0f * GetFrameTime();
        skyOffset += 1200.0f * GetFrameTime();
    }
    else {
        fWorldA -= 2.0f * GetFrameTime();
        skyOffset -= 1200.0f * GetFrameTime();
    }

    if (IsKeyDown(KEY_UP)) {
        fWorldX += cosf(fWorldA) * fSpeed * GetFrameTime();
        fWorldY += sinf(fWorldA) * fSpeed * GetFrameTime();
    }

    if (IsKeyDown(KEY_DOWN)) {
        fWorldX -= cosf(fWorldA) * fSpeed * GetFrameTime();
        fWorldY -= sinf(fWorldA) * fSpeed * GetFrameTime();
    }

    fWorldX += cosf(fWorldA) * fSpeed * GetFrameTime();
    fWorldY += sinf(fWorldA) * fSpeed * GetFrameTime();

    frustum.Far1.x = fWorldX + cosf(fWorldA - fFoVHalf) * fFar;
    frustum.Far1.y = fWorldY + sinf(fWorldA - fFoVHalf) * fFar;

    frustum.Near1.x = fWorldX + cosf(fWorldA - fFoVHalf) * fNear;
    frustum.Near1.y = fWorldY + sinf(fWorldA - fFoVHalf) * fNear;

    frustum.Far2.x = fWorldX + cosf(fWorldA + fFoVHalf) * fFar;
    frustum.Far2.y = fWorldY + sinf(fWorldA + fFoVHalf) * fFar;

    frustum.Near2.x = fWorldX + cosf(fWorldA + fFoVHalf) * fNear;
    frustum.Near2.y = fWorldY + sinf(fWorldA + fFoVHalf) * fNear;

    skyOffset = (float)fmod(skyOffset, texSky.width);
}
void Mode7::Draw()
{
    Rectangle skySource = { skyOffset, 0, (float)texSky.width, (float)texSky.height };
    Rectangle skyDest = { position.x, position.y, windowsize.x*blowup_scale , windowsize.y/2 * blowup_scale };
    DrawTexturePro(texSky, skySource, skyDest, { 0, 0 }, 0.0f, WHITE);

    for (int y = 0; y < windowsize.y / 2; y++) {
        DrawMode7Line(y);
    }

    DrawPlayer();


    //DrawText(TextFormat("Position: (%.1f, %.1f)", fWorldX, fWorldY),
    //    (int)(position.x + windowsize.x - 300),
    //    (int)(position.y + 30),
    //    20,
    //    YELLOW);

}
void Mode7::unload()
{
    UnloadTexture(texSky);
    UnloadTexture(texMap);
    UnloadImage(imgMap);
}
void Mode7::DrawPlayer()
{
   
    counter++;

    if (right)
    {
        if (playersprites > 0 && counter >2)
        {
            counter = 0;
            playersprites--;
        }
    }
    else 
    {
        if (playersprites < 5 && counter > 2)
        {
            counter = 0;
            playersprites++;
        }
    }
    DrawTexture(player[playersprites], (int)(position.x+windowsize.x+50 ), (int)(position.y+windowsize.y*2 + 190), WHITE);
}

