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
            if (!it.second.is_drawn )
            {
                double dx = it.first.x - (double)texX;
                double dy = it.first.y - (double)texY;
                
                

                if (std::hypot(dx, dy) < 35)
                {
                    
                    //DrawTexture(trafficlightsTex, ((int)position.x + x * blowup_scale) - trafficlightsTex.width / 2, ((int)position.y + blowup_scale * ((int)windowsize.y / 2 + y)) - trafficlightsTex.height, WHITE);
                    float scale = 1;

                    DrawTextureEx(trafficlightsTex, { (x * blowup_scale) - ((trafficlightsTex.width / 2) / scale), (blowup_scale * (windowsize.y / 2 + y) ) - (trafficlightsTex.height / scale) },
                        0,
                        scale
                        ,WHITE);
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
    trafficlightsTex = LoadTexture("Assets/tree.png");

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
    imgMap = LoadImageFromTexture(texMap);

    fPlayerScreenX = (float)Engine::GetWindow().GetSize().x / 2;
}
void Mode7::Update()
{
    if (IsKeyDown(KEY_Q)) fNear += 10 * GetFrameTime();

    if (IsKeyDown(KEY_A)) fNear -= 10 * GetFrameTime();

    if (IsKeyDown(KEY_W)) fFar += 10 * GetFrameTime();

    if (IsKeyDown(KEY_S)) fFar -= 10 * GetFrameTime();

    if (IsKeyDown(KEY_Z)) fFoVHalf += 0.1f * GetFrameTime();

    if (IsKeyDown(KEY_X)) fFoVHalf -= 0.1f * GetFrameTime();

    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT)) {
        if (IsKeyDown(KEY_RIGHT)) {

            right = true;
            playerXspeed += playerAccel * GetFrameTime();

        }
        else if (IsKeyDown(KEY_LEFT)) {
            right = false;
            playerXspeed -= playerAccel * GetFrameTime();
        }
        else {

            if (playerXspeed > 0.0f) {
                playerXspeed -= playerFriction * GetFrameTime();
                if (playerXspeed < 0.0f) playerXspeed = 0.0f;
            }
            else if (playerXspeed < 0.0f) {
                playerXspeed += playerFriction * GetFrameTime();
                if (playerXspeed > 0.0f) playerXspeed = 0.0f;
            }
        }
        
        if (right == true)
        {


            /*if (fSpeed < 300) {
                fSpeed = 300;
            }

            fRotationSpeed += fRotationAccel * GetFrameTime();
            fSpeed = fSpeed - abs(fRotationSpeed);

            if (fRotationSpeed > fMaxRotationSpeed) {
                fRotationSpeed = fMaxRotationSpeed;
            }*/

        }
        if (right == false)
        {




            /* if (fSpeed < 300) {
                 fSpeed = 300;
             }

             fRotationSpeed -= fRotationAccel * GetFrameTime();
             fSpeed = fSpeed - abs(fRotationSpeed);

             if (fRotationSpeed < -fMaxRotationSpeed) {
                 fRotationSpeed = -fMaxRotationSpeed;
             }*/

        }
        
    }
    playerXOffset += playerXspeed * GetFrameTime();
    if (playerXOffset <= leftWall || playerXOffset >= rightWall) {
        if (playerXOffset <= leftWall) {
            playerXOffset = leftWall;
            playerXspeed = 0;
            if (fSpeed < 300) {
                fSpeed = 300;
            }

            fRotationSpeed += fRotationAccel * GetFrameTime();
            fSpeed = fSpeed - abs(fRotationSpeed);

            if (fRotationSpeed > fMaxRotationSpeed) {
                fRotationSpeed = fMaxRotationSpeed;
            }

            fWorldA -= wallBounceRotation * GetFrameTime();

        }

        // 우측 벽 충돌
        if (playerXOffset >= rightWall) {
            playerXOffset = rightWall;
            playerXspeed = 0;

            if (fSpeed < 300) {
                fSpeed = 300;
            }

            fRotationSpeed -= fRotationAccel * GetFrameTime();
            fSpeed = fSpeed - abs(fRotationSpeed);

            if (fRotationSpeed < -fMaxRotationSpeed) {
                fRotationSpeed = -fMaxRotationSpeed;
            }
            fWorldA += wallBounceRotation * GetFrameTime();
        }
        
        /*fWorldX += cosf(fWorldA) * fSpeed * GetFrameTime();
        fWorldY += sinf(fWorldA) * fSpeed * GetFrameTime();*/
    }
    

   // fWorldA += fRotationSpeed * GetFrameTime();
    skyOffset += 400.0f * fRotationSpeed * GetFrameTime();



    fWorldX += cosf(fWorldA) * fSpeed * GetFrameTime();
    fWorldY += sinf(fWorldA) * fSpeed * GetFrameTime();


   // fWorldY += fSpeed * GetFrameTime();
    //fWorldA = 0.0f;

 /*   frustum.Far1.x = fWorldX - fFoVHalf * fFar;
    frustum.Far1.y = fWorldY + fFar;

    frustum.Near1.x = fWorldX - fFoVHalf * fNear;
    frustum.Near1.y = fWorldY + fNear;

    frustum.Far2.x = fWorldX + fFoVHalf * fFar;
    frustum.Far2.y = fWorldY + fFar;

    frustum.Near2.x = fWorldX + fFoVHalf * fNear;
    frustum.Near2.y = fWorldY + fNear;*/
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
        if (playersprites > 0 && counter >3)
        {
            counter = 0;
            playersprites--;
        }
    }
    else 
    {
        if (playersprites < 5 && counter > 3)
        {
            counter = 0;
            playersprites++;
        }
    }
    float scale = 1;
    /*int player_screen_x = ((float)Engine::GetWindow().GetSize().x / 2 - ((VPplayer[playersprites].width / 2) / scale)+ playerXOffset);
    int player_screen_y = ((float)Engine::GetWindow().GetSize().y / 5 * 2) + ((VPplayer[playersprites].height / 2) / scale);
    DrawTexture(player[playersprites], player_screen_x, player_screen_y,0,scale, WHITE);*/
    DrawTextureEx(VPplayer[playersprites], { (float)Engine::GetWindow().GetSize().x / 2 - ((VPplayer[playersprites].width / 2) / scale)+ playerXOffset,
        ((float)Engine::GetWindow().GetSize().y / 5 * 2) + (VPplayer[playersprites].height / 2) / scale },
        0, 
        scale,
        WHITE);
}

