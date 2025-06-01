#include "Mode7.h"
#include <cmath>
//https://www.youtube.com/watch?v=0kVM6dJeWaY




Color Mode7::DrawFog(Color color)
{
    
    
    A+= 1;
    
    
    
    Color fog = { (unsigned char)(BASE + R),(unsigned char)(BASE + G),(unsigned char)(BASE + B),(unsigned char)(BASE + A) };

    Color fogcolor = ColorTint(color, fog);
        
    return fogcolor;
}
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
        
        Color fogcolor = color;

        //DrawRectangle((int)position.x + x * blowup_scale, (int)position.y + blowup_scale * ((int)windowsize.y / 2 + y), blowup_scale, blowup_scale, Mode7::DrawFog(color));

        DrawRectangle((int)position.x + x * blowup_scale, (int)position.y + blowup_scale * ((int)windowsize.y / 2 + y), blowup_scale, blowup_scale, color);

        for (auto it : newMapGen::mapsprites)
        {
            if (!it.second.is_drawn)
            {
                double dx = it.first.x - (double)texX;
                double dy = it.first.y - (double)texY;

                float scale = 2.5f * fSampleDepth; //the reason why I used 2.5f is make scale size more maximize

                if (std::hypot(dx, dy) < 50.0f)
                {

                    float drawx = (float)(x * blowup_scale) - (trafficlightsTex.width * scale / 2.0f);
                    float drawy = blowup_scale * (windowsize.y / 2 + y) - trafficlightsTex.height * scale;

                    DrawTextureEx(trafficlightsTex, { drawx, drawy }, 0, scale, WHITE);
                    it.second.is_drawn = true;
                }
            }
        }
    }
}

void Mode7::Load()
{
    texSky = LoadTexture("Assets/Sky.png");

    texMap = LoadTexture("CreatedMap.png");
    windowtabs = LoadTexture("Assets/windowtabs.png");
    trafficlightsTex = LoadTexture("Assets/tree/dithered-image(2).png");
    player[0] = LoadTexture("Assets/Player/PlayerLeft-1.png");
    player[1] = LoadTexture("Assets/Player/PlayerLeft-2.png");
    player[2] = LoadTexture("Assets/Player/PlayerLeft-3.png");
    player[3] = LoadTexture("Assets/Player/PlayerRight-1.png");
    player[4] = LoadTexture("Assets/Player/PlayerRight-2.png");
    player[5] = LoadTexture("Assets/Player/PlayerRight-3.png");
    BWplayer[0] = LoadTexture("Assets/Player/BW/1.png");
    BWplayer[1] = LoadTexture("Assets/Player/BW/2.png");
    BWplayer[2] = LoadTexture("Assets/Player/BW/3.png");
    BWplayer[3] = LoadTexture("Assets/Player/BW/4.png");
    BWplayer[4] = LoadTexture("Assets/Player/BW/5.png");
    BWplayer[5] = LoadTexture("Assets/Player/BW/6.png");
    VPplayer[0] = LoadTexture("Assets/Player/vaporwave/scanlines/1.png");
    VPplayer[1] = LoadTexture("Assets/Player/vaporwave/scanlines/2.png");
    VPplayer[2] = LoadTexture("Assets/Player/vaporwave/scanlines/3.png");
    VPplayer[3] = LoadTexture("Assets/Player/vaporwave/scanlines/4.png");
    VPplayer[4] = LoadTexture("Assets/Player/vaporwave/scanlines/5.png");
    VPplayer[5] = LoadTexture("Assets/Player/vaporwave/scanlines/6.png");
    trees[0] = LoadTexture("Assets/tree/dithered-image.png");
    trees[1] = LoadTexture("Assets/tree/dithered-image(1).png");
    trees[2] = LoadTexture("Assets/tree/dithered-image(2).png");

    FovplayerRight[0]  = LoadTexture("Assets/Player/POV/Right hand/1.png");
    FovplayerRight[1]  = LoadTexture("Assets/Player/POV/Right hand/2.png");
    FovplayerRight[2]  = LoadTexture("Assets/Player/POV/Right hand/3.png");
    FovplayerRight[3]  = LoadTexture("Assets/Player/POV/Right hand/4.png");
    FovplayerRight[4]  = LoadTexture("Assets/Player/POV/Right hand/5.png");
    FovplayerRight[5]  = LoadTexture("Assets/Player/POV/Right hand/6.png");
    FovplayerRight[6]  = LoadTexture("Assets/Player/POV/Right hand/7.png");
    FovplayerRight[7]  = LoadTexture("Assets/Player/POV/Right hand/8.png");
    FovplayerRight[8]  = LoadTexture("Assets/Player/POV/Right hand/9.png");
    FovplayerRight[9]  = LoadTexture("Assets/Player/POV/Right hand/10.png");
    FovplayerRight[10] = LoadTexture("Assets/Player/POV/Right hand/11.png");
    FovplayerRight[11] = LoadTexture("Assets/Player/POV/Right hand/12.png");
    FovplayerRight[12] = LoadTexture("Assets/Player/POV/Right hand/13.png");
    FovplayerRight[13] = LoadTexture("Assets/Player/POV/Right hand/14.png");
    FovplayerRight[14] = LoadTexture("Assets/Player/POV/Right hand/15.png");
    FovplayerRight[15] = LoadTexture("Assets/Player/POV/Right hand/16.png");
    FovplayerRight[16] = LoadTexture("Assets/Player/POV/Right hand/17.png");
    FovplayerRight[17] = LoadTexture("Assets/Player/POV/Right hand/18.png");
   

    FovplayerLeft[0]  = LoadTexture("Assets/Player/POV/Left hand/1.png");
    FovplayerLeft[1]  = LoadTexture("Assets/Player/POV/Left hand/2.png");
    FovplayerLeft[2]  = LoadTexture("Assets/Player/POV/Left hand/3.png");
    FovplayerLeft[3]  = LoadTexture("Assets/Player/POV/Left hand/4.png");
    FovplayerLeft[4]  = LoadTexture("Assets/Player/POV/Left hand/5.png");
    FovplayerLeft[5]  = LoadTexture("Assets/Player/POV/Left hand/6.png");
    FovplayerLeft[6]  = LoadTexture("Assets/Player/POV/Left hand/7.png");
    FovplayerLeft[7]  = LoadTexture("Assets/Player/POV/Left hand/8.png");
    FovplayerLeft[8]  = LoadTexture("Assets/Player/POV/Left hand/9.png");
    FovplayerLeft[9]  = LoadTexture("Assets/Player/POV/Left hand/10.png");
    FovplayerLeft[10] = LoadTexture("Assets/Player/POV/Left hand/11.png");
    FovplayerLeft[11] = LoadTexture("Assets/Player/POV/Left hand/12.png");
    FovplayerLeft[12] = LoadTexture("Assets/Player/POV/Left hand/13.png");
    FovplayerLeft[13] = LoadTexture("Assets/Player/POV/Left hand/14.png");
    FovplayerLeft[14] = LoadTexture("Assets/Player/POV/Left hand/15.png");
    FovplayerLeft[15] = LoadTexture("Assets/Player/POV/Left hand/16.png");
    FovplayerLeft[16] = LoadTexture("Assets/Player/POV/Left hand/17.png");
    FovplayerLeft[17] = LoadTexture("Assets/Player/POV/Left hand/18.png");



    imgMap = LoadImageFromTexture(texMap);

    fPlayerScreenX = (float)Engine::GetWindow().GetSize().x / 2;
}
void Mode7::Update()
{
    //-171
    if (IsKeyDown(KEY_Q)) fNear += 100 * GetFrameTime();

    if (IsKeyDown(KEY_A)) fNear -= 100 * GetFrameTime();

    if (IsKeyDown(KEY_W)) fFar += 500 * GetFrameTime();

    if (IsKeyDown(KEY_S)) fFar -= 500 * GetFrameTime();

    if (IsKeyDown(KEY_Z)) fFoVHalf += 0.1f * GetFrameTime();

    if (IsKeyDown(KEY_X)) fFoVHalf -= 0.1f * GetFrameTime();

  
    if (IsKeyDown(KEY_RIGHT)) {
        playersprites = 0;
        right = true;
        
    }
    else if (IsKeyDown(KEY_LEFT)) {
        playersprites = 0;
        right = false;
    }

    else {
        if (fSpeed < 600) {
            fSpeed += 10;
        }
        if (fRotationSpeed > 0.0f) {
            fRotationSpeed -= fRotationDamping * GetFrameTime();
            if (fRotationSpeed < 0.0f)
                fRotationSpeed = 0.0f;
        }
        else if (fRotationSpeed < 0.0f) {
            fRotationSpeed += fRotationDamping * GetFrameTime();
            if (fRotationSpeed > 0.0f)
                fRotationSpeed = 0.0f;
        }
    }
    if (right)
    {
        if (fSpeed < 300) {
            fSpeed = 300;
        }
        fRotationSpeed += fRotationAccel * GetFrameTime();
        fSpeed = fSpeed - abs(fRotationSpeed);
        if (fRotationSpeed > fMaxRotationSpeed)
            fRotationSpeed = fMaxRotationSpeed;

    }
    else
    {
        if (fSpeed < 300) {
            fSpeed = 300;
        }

        fRotationSpeed -= fRotationAccel * GetFrameTime();
        fSpeed = fSpeed - abs(fRotationSpeed);

        if (fRotationSpeed < -fMaxRotationSpeed)
            fRotationSpeed = -fMaxRotationSpeed;

    }
    
    
    fWorldA += fRotationSpeed * GetFrameTime();
    skyOffset += 400.0f * fRotationSpeed * GetFrameTime();

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
    //DrawTexturePro(texSky, skySource, skyDest, { 0, 0 }, 0.0f, WHITE);
    DrawPlayer();


    DrawText(TextFormat("Speed: %.1f",fSpeed),100,100,
        20,
        YELLOW);
    DrawText(TextFormat("fov: %.1f", fFoVHalf), 100, 200,
        20,
        YELLOW);
    DrawText(TextFormat("mousepos: %.1f, %.1f",GetMousePosition().x , GetMousePosition().y), 100, 300,
        20,
        YELLOW);
    DrawFPS(500, 100);
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
        if (playersprites < 18 && counter > 1)
        {
            counter = 0;
            playersprites++;
        }
        DrawTextureEx(FovplayerLeft[playersprites], { -600,110 }, 0, 2, WHITE);
    }
    else 
    {
        if (playersprites < 18 && counter > 1)
        {
            counter = 0;
            playersprites++;
        }
        DrawTextureEx(FovplayerRight[playersprites], { -600,110 }, 0, 2, WHITE);
    }


   /* DrawTextureEx(VPplayer[playersprites], { (float)Engine::GetWindow().GetSize().x / 2 - ((VPplayer[playersprites].width / 2) / scale),
        ((float)Engine::GetWindow().GetSize().y / 5 * 2) + (VPplayer[playersprites].height / 2) / scale },
        0, 
        scale,
        WHITE);*/
}

