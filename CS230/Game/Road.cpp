/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Road.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes,JunSeok Lee
Created:    March 8, 2023
*/

#pragma once
#include "Road.h"
#include "../Engine/Engine.h"

Road::Road()
{
    
    road.Load("Assets/groundtex.spt");
}

Road::Road(Math::vec2 start_position) :
    GameObject(start_position, 0.0, { 0.75,0.75 })
{
    road.Load("Assets/groundtex.spt");
}
void Road::Update([[maybe_unused]] double dt) {
    UpdateVelocity({ -GetVelocity().x * drag * dt,-GetVelocity().y * drag * dt });
    UpdatePosition({ GetVelocity().x * dt, GetVelocity().y * dt });
    sprite.Update(dt);

    object_matrix = Math::TranslationMatrix(position) * Math::RotationMatrix(GetRotation()) * Math::ScaleMatrix(scale);
}
void Road::Draw(Math::TransformationMatrix camera_matrix) {

    road.Draw(camera_matrix);
}
void Road::DrawPerspective(Math::TransformationMatrix camera_matrix) {

    road.DrawPerspective(camera_matrix);
}

