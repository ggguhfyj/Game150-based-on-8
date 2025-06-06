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
}

void Gam150::Draw() {
    Engine::GetWindow().Clear(0x222222FF);
    Mode7::Draw();
    
}       



void Gam150::Update([[maybe_unused]] double dt) {
    Mode7::Update();
    
    if (IsKeyReleased(KEY_U)) drawmode = 1;
    if (IsKeyReleased(KEY_J)) drawmode = 0;
    if (IsKeyReleased(KEY_SPACE) && TestMap::drawnRoadSegments < TestMap::Road_List.size() - 2)
    {
        TestMap::drawnRoadSegments += 2;
    }
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Escape)) {
        Engine::GetLogger().LogEvent("Setting next state to Gam150");
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::GameOver));
    }
}


void Gam150::Unload() {
    
    Mode7::unload();

}
