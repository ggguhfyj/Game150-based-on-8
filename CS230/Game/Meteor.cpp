/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Meteor.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, JunSeok Lee
Created:    April 30, 2025
Updated:   May 11, 2025
*/
#include"Meteor.h"
#include"../Engine/Engine.h"

Meteor::Meteor(Math::vec2 Window_Size) : CS230::GameObject({0,0}), Window_Size(Window_Size)
{
    sprite.Load("Assets/Meteor.spt");
    SetVelocity({ ((double)rand() / RAND_MAX * 2.0 - 1.0) * default_velocity, ((double)rand() / RAND_MAX * 2.0 - 1.0) * default_velocity });
    SetRotation((double)rand() / RAND_MAX * 2.0 * PI);
    SetPosition({ (double)rand() / RAND_MAX * Window_Size.x, (double)rand() / RAND_MAX * Window_Size.y });
}
    void Meteor::Update(double dt) {
        GameObject::Update(dt);
        if (GetPosition().x + static_cast<Math::vec2>(sprite.GetFrameSize()).x / 2.0 < 0) {
            SetPosition({ static_cast<double>(Window_Size.x) + static_cast<Math::vec2>(sprite.GetFrameSize()).x / 2.0, GetPosition().y });
        }
        else if (GetPosition().x - static_cast<Math::vec2>(sprite.GetFrameSize()).x / 2.0 > Window_Size.x) {
            SetPosition({ 0.0 - static_cast<Math::vec2>(sprite.GetFrameSize()).x / 2.0, GetPosition().y });
        }
        if (GetPosition().y + static_cast<Math::vec2>(sprite.GetFrameSize()).y / 2.0 < 0) {
            SetPosition({ GetPosition().x, static_cast<double>(Window_Size.y) + static_cast<Math::vec2>(sprite.GetFrameSize()).y / 2.0 });
        }
        else if (GetPosition().y - static_cast<Math::vec2>(sprite.GetFrameSize()).y / 2.0 > Window_Size.y) {
            SetPosition({ GetPosition().x, 0.0 - static_cast<Math::vec2>(sprite.GetFrameSize()).y / 2.0 });
        }
        Engine::GetLogger().LogDebug("Rotation: " + std::to_string(GetRotation()));
}