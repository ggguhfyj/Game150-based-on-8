#include "Mode7.h"
#include <cmath>

//https://www.youtube.com/watch?v=0kVM6dJeWaY




Color Mode7::DrawFog(Color color)
{


    A += 1;


    Color fog = { (unsigned char)(BASE + R),(unsigned char)(BASE + G),(unsigned char)(BASE + B),(unsigned char)(BASE + A) };

    Color fogcolor = ColorTint(color, fog);

    return fogcolor;
}
void Mode7::DrawMode7Line(int y) //y doesnt skip
{
    float slope_factor = 1.0f;
    if (pill_used == true) {
        slope_factor = 1.0f + 1.0f * sinf((float)GetTime() * 2.0f + y * 0.05f);
    }
    else {
        slope_factor = 1.0f;
    }
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

        Color fogcolor = color;

        //DrawRectangle((int)position.x + x * blowup_scale, (int)position.y + blowup_scale * ((int)windowsize.y / 2 + y), blowup_scale, blowup_scale, Mode7::DrawFog(color));

        DrawRectangle((int)position.x + x * blowup_scale, (int)position.y + blowup_scale * ((int)windowsize.y / 2 + y), blowup_scale, blowup_scale, color);

        for (auto it : newMapGen::mapsprites)
        {
            if (!it.second.is_drawn)
            {
                double dx = it.first.x - (double)texX;
                double dy = it.first.y - (double)texY;

                float scale = 2.5f * fSampleDepth * slope_factor; //the reason why I used 2.5f is make scale size more maximize

                if (std::hypot(dx, dy) < 50.0f)
                {

                    float drawx = (float)(x * blowup_scale) - (trafficlightsTex.width * scale / 2.0f);
                    float drawy = blowup_scale * (windowsize.y / 2 + y) - trafficlightsTex.height * scale;
                    if (it.second.sprite == newMapGen::spritetype::pill && pill_get == false && pill_timer.GetTime() == 0) {
                        drawx = (float)(x * blowup_scale) - (pill.width * scale / 2.0f);
                        drawy = blowup_scale * (windowsize.y / 2 + y) - pill.height * scale;
                        DrawTextureEx(pill, { drawx, drawy }, 0, scale, WHITE);
                    }
                    else if (it.second.sprite == newMapGen::spritetype::coin) {
                        drawx = (float)(x * blowup_scale) - (coin.width * scale / 2.0f);
                        drawy = blowup_scale * (windowsize.y / 2 + y) - coin.height * scale;
                        DrawTextureEx(coin, { drawx, drawy }, 0, scale, WHITE);
                    }
                    else {
                        DrawTextureEx(trafficlightsTex, { drawx, drawy }, 0, scale, WHITE);
                    }
                    
                    if ((x * blowup_scale) > 550 && (x * blowup_scale) < 650)
                        if ((blowup_scale * (windowsize.y / 2 + y)) > 750 && (blowup_scale * (windowsize.y / 2 + y)) < 800)
                        {
                            if (it.second.sprite == newMapGen::spritetype::pill && pill_get == false) {
                                pill_get = true;
                            }
                            if (it.second.sprite == newMapGen::spritetype::coin) {
                                money += Get_money;
                            }
                            if (it.second.sprite == newMapGen::spritetype::tree1 || 
                                it.second.sprite == newMapGen::spritetype::tree2) {
                                Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::GameOver));
                            }
                        }
                    if (blowup_scale * (windowsize.y / 2 + y) > 700 && blowup_scale * (windowsize.y / 2 + y) < 850) {
                        if (!close_call_playing) {
                            if (it.second.sprite == newMapGen::spritetype::tree1 ||
                                it.second.sprite == newMapGen::spritetype::tree2) {
                                score += 1;
                                if (pill_used) {
                                    score += 2;
                                }
                            }
                            
                            float centerX = windowsize.x * blowup_scale / 2.0f;
                            float distanceFromCenter = abs(x * blowup_scale - centerX);
                            float maxDistance = windowsize.x * blowup_scale / 2.0f;

                            float volume = 1.0f - (distanceFromCenter / maxDistance) * 0.9f;
                            volume = fmax(0.1f, volume);

                            SetSoundVolume(sound_close_call, volume);
                            PlaySound(sound_close_call);
                            close_call_playing = true;
                            Engine::GetLogger().LogEvent("playing close call music now");
                        }
                    }
                    }
                    //if ((blowup_scale * (windowsize.y / 2 + y)) > 650 && (blowup_scale * (windowsize.y / 2 + y)) < 00)
                    //if (((x * blowup_scale) > -50) && ((x * blowup_scale) < 1250))
                    //{
                    //    if (!close_call_playing)
                    //    {
                    //        //this is happening way too much causing lag spikes
                    //        float centerX = windowsize.x * blowup_scale / 2.0f;
                    //        float distanceFromCenter = abs(x * blowup_scale - centerX);
                    //        float maxDistance = windowsize.x * blowup_scale / 2.0f;

                    //        float volume = 1.0f - (distanceFromCenter / maxDistance) * 0.9f;
                    //        volume = fmax(0.1f, volume);

                    //        SetSoundVolume(sound_close_call, volume);
                    //        PlaySound(sound_close_call);
                    //        close_call_playing = true;
                    //        Engine::GetLogger().LogEvent("playing close call music now");
                    //    }
                    //    

                    //}
                    it.second.is_drawn = true;
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
    pill = LoadTexture("Assets/pill.png");
    coin = LoadTexture("Assets/coin.png");
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

    FovplayerRight[0] = LoadTexture("Assets/Player/POV/Right hand/1.png");
    FovplayerRight[1] = LoadTexture("Assets/Player/POV/Right hand/2.png");
    FovplayerRight[2] = LoadTexture("Assets/Player/POV/Right hand/3.png");
    FovplayerRight[3] = LoadTexture("Assets/Player/POV/Right hand/4.png");
    FovplayerRight[4] = LoadTexture("Assets/Player/POV/Right hand/5.png");
    FovplayerRight[5] = LoadTexture("Assets/Player/POV/Right hand/6.png");
    FovplayerRight[6] = LoadTexture("Assets/Player/POV/Right hand/7.png");
    FovplayerRight[7] = LoadTexture("Assets/Player/POV/Right hand/8.png");
    FovplayerRight[8] = LoadTexture("Assets/Player/POV/Right hand/9.png");
    FovplayerRight[9] = LoadTexture("Assets/Player/POV/Right hand/10.png");
    FovplayerRight[10] = LoadTexture("Assets/Player/POV/Right hand/11.png");
    FovplayerRight[11] = LoadTexture("Assets/Player/POV/Right hand/12.png");
    FovplayerRight[12] = LoadTexture("Assets/Player/POV/Right hand/13.png");
    FovplayerRight[13] = LoadTexture("Assets/Player/POV/Right hand/14.png");
    FovplayerRight[14] = LoadTexture("Assets/Player/POV/Right hand/15.png");
    FovplayerRight[15] = LoadTexture("Assets/Player/POV/Right hand/16.png");
    FovplayerRight[16] = LoadTexture("Assets/Player/POV/Right hand/17.png");
    FovplayerRight[17] = LoadTexture("Assets/Player/POV/Right hand/18.png");


    FovplayerLeft[0] = LoadTexture("Assets/Player/POV/Left hand/1.png");
    FovplayerLeft[1] = LoadTexture("Assets/Player/POV/Left hand/2.png");
    FovplayerLeft[2] = LoadTexture("Assets/Player/POV/Left hand/3.png");
    FovplayerLeft[3] = LoadTexture("Assets/Player/POV/Left hand/4.png");
    FovplayerLeft[4] = LoadTexture("Assets/Player/POV/Left hand/5.png");
    FovplayerLeft[5] = LoadTexture("Assets/Player/POV/Left hand/6.png");
    FovplayerLeft[6] = LoadTexture("Assets/Player/POV/Left hand/7.png");
    FovplayerLeft[7] = LoadTexture("Assets/Player/POV/Left hand/8.png");
    FovplayerLeft[8] = LoadTexture("Assets/Player/POV/Left hand/9.png");
    FovplayerLeft[9] = LoadTexture("Assets/Player/POV/Left hand/10.png");
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

    sound_close_call = LoadSound("Assets/close_call.wav");
    sound_ski_skidding = LoadSound("Assets/ski_skidding.wav");
    sound_ski_default = LoadMusicStream("Assets/ski_default.wav");
    sound_wind = LoadMusicStream("Assets/wind_.wav");
    isSkiddingSoundPlaying = false;
    close_call_playing = false;
    windPlaying = false;
    PlayMusicStream(sound_ski_default);
    PlayMusicStream(sound_wind);
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


    if (IsKeyPressed(KEY_RIGHT)) {
        playersprites = 0;
        right = true;

    }
    else if (IsKeyPressed(KEY_LEFT)) {
        playersprites = 0;
        right = false;
    }

    else {
        if (fSpeed < fMaxSpeed) {
            fSpeed += 10;
        }
        if (fSpeed >= fMaxSpeed - 10) {//sound volume stuff

            SetMusicVolume(sound_wind, musicVolume * 2);
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

    if (score == 10) {
        SetDifficulty(static_cast<Difficulty>(static_cast<int>(current_difficulty) + 1));
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
    if (pill_used == false && Engine::GetInput().KeyJustPressed(CS230::Input::Keys::E)) {
        pill_used = true;
        pill_get = false;
        pill_timer.Reset(10.0);
    }
    if (pill_used == true) {
        pill_timer.Update(GetFrameTime());

        if (pill_timer.GetTime() <= 0) {
            pill_used = false;
        }
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

    SetMusicVolume(sound_ski_default, musicVolume);
    SetSoundVolume(sound_ski_skidding, soundVolume);

    if (close_call_playing && !IsSoundPlaying(sound_close_call)) {
        close_call_playing = false;
    }

    UpdateMusicStream(sound_ski_default);
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT)) {
        if (!isSkiddingSoundPlaying) {
            PlaySound(sound_ski_skidding);
            isSkiddingSoundPlaying = true;
            //Engine::GetLogger().LogEvent("playing music now");
        }
    }
    else {
        isSkiddingSoundPlaying = false;
    }
    float base_speed = 600.0f;
    float speed_multiplier = 1.0f;
    switch (current_difficulty) {
    case Difficulty::Easy: speed_multiplier = 0.7f; Get_money = 0.0008f; break;
    case Difficulty::Normal: speed_multiplier = 1.0f; Get_money = 0.0018f; break;
    case Difficulty::Hard: speed_multiplier = 1.5f; Get_money = 0.0028f; break;
    case Difficulty::special:  if (!pill_used) {
        pill_used = true;
        pill_timer.Reset(30.0);
    }
                            speed_multiplier = 2.0f;
                            Get_money = Get_money = 0.0035f;
                            break;
    }
    fMaxSpeed = base_speed * speed_multiplier;
    if (score > high_score) {
        high_score = score;
    }
}
void Mode7::Draw()
{
    Rectangle skySource = { skyOffset, 0, (float)texSky.width, (float)texSky.height };
    Rectangle skyDest = { position.x, position.y, windowsize.x * blowup_scale , windowsize.y / 2 * blowup_scale };

    DrawTexturePro(texSky, skySource, skyDest, { 0, 0 }, 0.0f, WHITE);
    for (int y = 0; y < windowsize.y / 2; y++) {
        DrawMode7Line(y);
    }
    //DrawTexturePro(texSky, skySource, skyDest, { 0, 0 }, 0.0f, WHITE);
    DrawPlayer();


    DrawText(TextFormat("Speed: %.1f", fSpeed), 100, 100,
        20,
        YELLOW);
    DrawText(TextFormat("fov: %.1f", fFoVHalf), 100, 200,
        20,
        YELLOW);
    DrawText(TextFormat("mousepos: %.1f, %.1f", GetMousePosition().x, GetMousePosition().y), 100, 300,
        20,
        YELLOW);
    DrawText(TextFormat("Pill : %s", pill_get ? "ture" : "false"), GetScreenWidth() - 400, 20, 50, RED);
    DrawText(TextFormat("Money : %d",static_cast<int>(money)), GetScreenWidth() - 400, 80, 30, RED);
    if (pill_used == true) {
        DrawText(TextFormat("pill time remaining : %.2f", pill_timer.GetTime()), 100, 400, 30, RED);
    }
    DrawText(TextFormat("score : %d", score), 100, 700, 30, RED);
    DrawFPS(500, 100);
}
void Mode7::unload()
{
    UnloadTexture(texSky);
    UnloadTexture(texMap);
    UnloadImage(imgMap);

    UnloadSound(sound_ski_skidding);
    UnloadSound(sound_close_call);
    StopMusicStream(sound_ski_default);
    UnloadMusicStream(sound_ski_default);
    UnloadMusicStream(sound_wind);
    newMapGen::UnloadTexture();
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

void Mode7::SetVolume(float volume)
{
    musicVolume = volume;
    soundVolume = volume;
    SetMusicVolume(sound_ski_default, musicVolume);
    SetSoundVolume(sound_ski_skidding, soundVolume);
    SetSoundVolume(sound_close_call, soundVolume);
    SetMusicVolume(sound_wind, musicVolume);
}

void Mode7::SetDifficulty(Difficulty diff) {
    current_difficulty = diff;
}
