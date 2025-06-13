/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Gam150.cpp
Project:    CS230 Engine
Author:     Junseok Lee
Created:    March 11, 2025
Updated:        March 23, 2025
*/

#include "../Engine/Engine.h"
#include "States.h"
#include "..\Game\Gam150.h"

Gam150::Gam150()
{
    
}

void Gam150::Load() {
    newMapGen::LoadTextures();
    newMapGen::generatesnowTexture();
    Mode7::Load();
    target = LoadRenderTexture(Engine::GetWindow().GetSize().x, Engine::GetWindow().GetSize().y);

    fish = LoadShader(0,"Assets/shaders/fisheye.fs");
    scanlines = LoadShader(0, "Assets/shaders/scanlines.fs");
    downhillShader = LoadShader(0, "Assets/shaders/123.fs");
    Engine::GetWindow().Clear(0x00000000);
}

void Gam150::Draw() {
    Engine::GetWindow().Clear(0x222222FF);
    // 1. Draw the 3D scene to a texture
    BeginTextureMode(target);
    
    Mode7::Draw();
    EndTextureMode();

    // 2. Draw the texture to the screen, applying the downhill shader
    BeginShaderMode(downhillShader);
    // Get the location of the "hillFactor" uniform in the shader
    int hillFactorLoc = GetShaderLocation(downhillShader, "hillFactor");
    // Send the value of our hillFactor variable to the shader
    SetShaderValue(downhillShader, hillFactorLoc, &hillFactor, SHADER_UNIFORM_FLOAT);

    // Draw the rendered texture. It's flipped vertically to match OpenGL's coordinate system.
    DrawTextureRec(target.texture, { 0, 0, (float)target.texture.width, (float)-target.texture.height }, { 0, 0 }, WHITE);
    EndShaderMode();
}


void Gam150::Update([[maybe_unused]] double dt) {
    Mode7::Update();

    // Allow changing the hillFactor for testing purposes
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::I)) {
        hillFactor += 0.1f * (float)dt;
        if (hillFactor > 1.0f) hillFactor = 1.0f;
    }
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::K)) {
        hillFactor -= 0.1f * (float)dt;
        if (hillFactor < 0.0f) hillFactor = 0.0f;
    }

    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Escape)) {
        Engine::GetLogger().LogEvent("Setting next state to Gam150");
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::GameOver));
    }
}

void Gam150::Unload() {
    Mode7::unload();
    UnloadRenderTexture(target);
    UnloadShader(fish);
    UnloadShader(scanlines);
    UnloadShader(downhillShader); // <--- Unload the shader
}