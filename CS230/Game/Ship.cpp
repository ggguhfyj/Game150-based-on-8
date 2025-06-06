/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Cat.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes,JunSeok Lee
Created:    March 8, 2023
*/

#pragma once
#include "Ship.h"
#include "../Engine/Engine.h"

Ship::Ship(Math::vec2 start_position) :
    GameObject(start_position, 0.0, {0.75,0.75})
{
    sprite.Load("Assets/Ship.spt");
    flame_left.Load("Assets/Flame.spt");
    flame_right.Load("Assets/Flame.spt");

}

//void Ship::Load() {
//    sprite.Load("Assets/Ship.spt");
//    flame_left.Load("Assets/Flame.spt");
//    flame_right.Load("Assets/Flame.spt");
//    velocity = { 0, 0 };
//    position = start_position;
//    flame_is_on = false;
//    drawflame = false;
//    angle = 0.0;
//}

void Ship::Update([[maybe_unused]] double dt) {
    bool IsWDown = Engine::GetInput().KeyDown(CS230::Input::Keys::W);
    if (IsWDown != flame_is_on) {
        flame_is_on = IsWDown;
        int anim = flame_is_on
            ? static_cast<int>(FlameAnim::Flame)
            : static_cast<int>(FlameAnim::None);

        flame_left.PlayAnimation(anim);
        flame_right.PlayAnimation(anim);
    }
    
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::W)) {
        drawflame = true;
        //velocity +=;
        UpdateVelocity(Math::RotationMatrix(GetRotation()) * Math::vec2{0,speed*dt});
    }
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::S)) {
        drawflame = true;
      
        UpdateVelocity(Math::RotationMatrix(GetRotation()) * Math::vec2{ 0,-speed * dt });
    }
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::A)) {
        //angle+= rotation_speed;
        UpdateRotation(rotation_speed*dt);
    }
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::D)) {
        //angle-= rotation_speed;
        UpdateRotation(-rotation_speed*dt);
    }
    //velocity -= velocity * drag * dt;
    UpdateVelocity({ -GetVelocity().x * drag*dt,-GetVelocity().y * drag*dt});
    //Engine::GetLogger( ).LogDebug("Velocity: " + std::to_string(GetVelocity().x) + ", " + std::to_string(GetVelocity().y));

    //position += velocity * dt;
    UpdatePosition({ GetVelocity().x * dt, GetVelocity().y * dt });

   

    flame_right.Update(dt);
    flame_left.Update(dt);
    sprite.Update(dt);

    //object_matrix = Math::TranslationMatrix(position) * Math::RotationMatrix(GetRotation()) * Math::ScaleMatrix(scale);
}

void Ship::Draw(Math::TransformationMatrix camera_matrix) {
    if (drawflame)
    {
        flame_left.Draw(camera_matrix * Math::RotationMatrix(GetRotation()) * Math::ScaleMatrix(scale) * Math::TranslationMatrix(static_cast<Math::vec2>(sprite.GetHotSpot(1))));
        flame_right.Draw(camera_matrix * Math::RotationMatrix(GetRotation()) * Math::ScaleMatrix(scale) * Math::TranslationMatrix(static_cast<Math::vec2>(sprite.GetHotSpot(2))));
        
    }
    //*camera_matrix
    sprite.Draw(camera_matrix * Math::RotationMatrix(GetRotation()) * Math::ScaleMatrix(scale));

}


//void Ship::Reset() {
//    position = start_position;
//    velocity = { 0.0, 0.0 };
//}