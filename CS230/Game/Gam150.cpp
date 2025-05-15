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
    TestMap::Initialize_Map();
    TestMap::TestDrawMap();
    TestMap::TestDrawMap2();
    TestMap::Generate_roads({ {2},{5},{0} });
    TestMap::Generate_TrafficLights();
    TestMap::CreateMapTexture({ 50.0,300.0 }, 1);
    Mode7::Load();
    
}

void Gam150::Draw() {
    Engine::GetWindow().Clear(0x222222FF);
    TestMap::drawMap({ 50.0,300.0 }, 1);
    if (drawmode)Mode7::Draw();
}       



void Gam150::Update([[maybe_unused]] double dt) {
    Mode7::Update();
    
    if (IsKeyReleased(KEY_U)) drawmode = 1;
    if (IsKeyReleased(KEY_J)) drawmode = 0;
    if (IsKeyReleased(KEY_SPACE) && TestMap::drawnRoadSegments < TestMap::Road_List.size() - 2)
    {
        TestMap::drawnRoadSegments += 2;
    }
    if (IsKeyPressed(KEY_ONE)) {
        TestMap::Generate_Expressway1();
    }

    if (IsKeyPressed(KEY_TWO)) {
        TestMap::Generate_Expressway2();
    }

    if (IsKeyPressed(KEY_THREE)) {
        TestMap::Generate_Expressway3();
    }

    if (IsKeyPressed(KEY_C)) {
        
    }

}


void Gam150::Unload() {
    
    Mode7::unload();

}
