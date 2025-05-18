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
#include <iostream>
#include <functional>
#include <vector>
#include <raylib.h>

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
int currentExpresswayIndex = 1;
int lastDrawnExpresswayIndex = 0;
std::vector<std::function<void()>> expresswayGenerators = {
      TestMap::Generate_Expressway1,
      TestMap::Generate_Expressway2,
      TestMap::Generate_Expressway3,
      TestMap::Generate_Expressway4,
      TestMap::Generate_Expressway5,
      TestMap::Generate_Expressway6,
};
void Gam150::Update([[maybe_unused]] double dt) {
    Mode7::Update();
    
    if (IsKeyReleased(KEY_U)) drawmode = 1;
    if (IsKeyReleased(KEY_J)) drawmode = 0;
    if (IsKeyReleased(KEY_SPACE) && TestMap::drawnRoadSegments < TestMap::Road_List.size() - 2)
    {
        TestMap::drawnRoadSegments += 2;
    }
    if (IsKeyPressed(KEY_TAB)) {
        expresswayGenerators[currentExpresswayIndex]();
        lastDrawnExpresswayIndex = currentExpresswayIndex;
        currentExpresswayIndex = (currentExpresswayIndex + 1) % expresswayGenerators.size();
    }
    if (lastDrawnExpresswayIndex == -1) {
        DrawText("Expressway: none", 60, 100, 50, GRAY);
    }
    else {
        DrawText(TextFormat("Expressway: %d", lastDrawnExpresswayIndex + 1), 60, 150, 50, DARKBLUE);
    }
    if (IsKeyPressed(KEY_C)) {
        
    }

}


void Gam150::Unload() {
    
    Mode7::unload();

}
