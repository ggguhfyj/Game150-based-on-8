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
#include "Gam150Player.h"
#include "../Engine/Engine.h"

Gam150Player::Gam150Player(Math::vec2 start_position) :
    GameObject(start_position, 0.0, { 0.75,0.75 })
{
    sprite.Load("Assets/Gam150Player.spt");


}


void Gam150Player::Update([[maybe_unused]] double dt) {
    
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::W)) {
       
        //we wont be changing the position of the player but rather the map itself

    }

    if (Engine::GetInput().KeyDown(CS230::Input::Keys::A)) {
        
        UpdateRotation(rotation_speed * dt);
    }
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::D)) {
        //angle-= rotation_speed;
        UpdateRotation(-rotation_speed * dt);
    }
    //velocity -= velocity * drag * dt;
    UpdateVelocity({ -GetVelocity().x * drag * dt,-GetVelocity().y * drag * dt });
    Engine::GetLogger().LogDebug("Velocity: " + std::to_string(GetVelocity().x) + ", " + std::to_string(GetVelocity().y));

    //position += velocity * dt;
    UpdatePosition({ GetVelocity().x * dt, GetVelocity().y * dt });

    Math::ivec2 windowSize = Engine::GetWindow().GetSize();
    Math::ivec2 spriteSize = sprite.GetFrameSize();

    if (GetPosition().x < -spriteSize.x) {
        SetPosition({ (double)windowSize.x,GetPosition().y });

    }
    else if (GetPosition().x - spriteSize.x / 2 > windowSize.x) {
        SetPosition({ -(double)spriteSize.x,GetPosition().y });
    }

    if (GetPosition().y < -spriteSize.y) {
        //position.y = windowSize.y;
        SetPosition({ GetPosition().x ,(double)windowSize.y, });
    }
    else if (GetPosition().y - spriteSize.y / 2 > windowSize.y) {
        //position.y = -spriteSize.y;
        SetPosition({ GetPosition().x ,-(double)spriteSize.y, });
    }
    flame_right.Update(dt);
    flame_left.Update(dt);
    sprite.Update(dt);
    object_matrix = Math::TranslationMatrix(position) * Math::RotationMatrix(GetRotation()) * Math::ScaleMatrix(scale);
}

void Gam150Player::Draw(Math::TransformationMatrix camera_matrix) {
 

    sprite.Draw(GetMatrix() * camera_matrix);
}

