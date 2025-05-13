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

Math::SkewMatrix skew_matrix = Math::SkewMatrix(2, 5);

Gam150::Gam150() :
    camera({ { 0.15 * Engine::GetWindow().GetSize().x, 0 }, { 0.15 * Engine::GetWindow().GetSize().x, 0 } })//player zone
{
    //skew_matrix
}

void Gam150::Load() {

    car_ptr = new Car({ (double)Engine::GetWindow().GetSize().x/2,(double)Engine::GetWindow().GetSize().y/2 });
    road_ptr = new Road({ 0,0 });

    gameobjectmanager.Add(road_ptr);
    gameobjectmanager.Add(car_ptr);//start position is set to 0,0
    

   
    camera.SetPosition({ 0,0 });
    camera.SetLimit({ { 0,0 }, {0,0} });
    
    TestMap::Initialize_Map();
    TestMap::TestDrawMap();
    TestMap::TestDrawMap2();
    TestMap::Generate_roads({ {2},{5},{0} });
    
}

void Gam150::Draw() {
    Engine::GetWindow().Clear(0x222222FF);
    //if (draw mode == normal) {
    //    gameobjectmanager.DrawAll(camera.Get0ffsetMatrix());
    //}
    //else if (draw mode == mode7) {
    //    car.visible = false;
    //    gameobjectmanager.DrawAll(camera.GetoffsetMatrix() * skew_matrix);//switch it around or smth tranlation
    //    draw inside of car
    //}
    gameobjectmanager.DrawAll(camera.GetoffsetMatrix() );
    
    if (IsKeyReleased(KEY_SPACE) && TestMap::drawnRoadSegments < TestMap::Road_List.size() - 2)
    {
        TestMap::drawnRoadSegments += 2;
    }
    TestMap::drawMap({ 50.0,300.0 }, 1);
}



void Gam150::Update([[maybe_unused]] double dt) {
    gameobjectmanager.UpdateAll(dt);
    camera.SetPosition({ car_ptr->GetPosition() });
    
    camera.SetRotation(car_ptr->GetRotation());
    //car and camera position are the same but the drawing is making the car not ceneterd
    //Engine::GetLogger().LogEvent("CAR"+std::to_string(car_ptr->GetPosition().x) + " , " + std::to_string(car_ptr->GetPosition().y) + "\n");
    //Engine::GetLogger().LogEvent("CAMERA"+std::to_string(camera.GetPosition().x) + " , " + std::to_string(camera.GetPosition().y) + "\n");
}



void Gam150::Unload() {
    //background.Unload();
    gameobjectmanager.Unload();

}
