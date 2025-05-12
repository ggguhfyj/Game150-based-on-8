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



Gam150::Gam150() :
    camera({ { 0.15 * Engine::GetWindow().GetSize().x, 0 }, { 0.35 * Engine::GetWindow().GetSize().x, 0 } })
{

}

void Gam150::Load() {


    background.Add("Assets/Planets.png", 0.25);
    background.Add("Assets/Ships.png", 0.5);
    background.Add("Assets/Foreground.png", 1);


    camera.SetPosition({ 0,0 });
    camera.SetLimit({ { 0,0 }, { background.GetSize().x - Engine::GetWindow().GetSize().x, background.GetSize().y - Engine::GetWindow().GetSize().y } });
    /////////
    TestMap::Initialize_Map();
    TestMap::TestDrawMap();
    TestMap::TestDrawMap2();
    TestMap::Generate_roads({ {2},{5},{0} });
}

void Gam150::Update([[maybe_unused]] double dt) {
    gameobjectmanager.UpdateAll(dt);


    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Enter)) {
       // Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Mode2));
    }
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::R)) {
        Engine::GetGameStateManager().ReloadState();
    }
  

}

void Gam150::Draw() {
    Engine::GetWindow().Clear(0x222222FF);
    //background.Draw(camera);
    gameobjectmanager.DrawAll(camera.GetMatrix());
   ///////
    if (IsKeyReleased(KEY_SPACE) && TestMap::drawnRoadSegments < TestMap::Road_List.size() - 2)
    {
        TestMap::drawnRoadSegments += 2;

    }
    TestMap::drawMap({ 50.0,300.0 }, 1);
}




void Gam150::Unload() {
    background.Unload();
    gameobjectmanager.Unload();

}
