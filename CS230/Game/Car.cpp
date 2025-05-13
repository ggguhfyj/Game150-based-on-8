/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Car.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes,JunSeok Lee
Created:    March 8, 2023/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Cat.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes,JunSeok Lee
Created:    March 8, 2023
*/

#pragma once
#include "Car.h"
#include "../Engine/Engine.h"

Car::Car()
{
    car.Load("Assets/ship.spt");
}

Car::Car(Math::vec2 start_position) :
    GameObject(start_position, 0.0, { 0.75,0.75 })//start pos, rotation and scale.
{
    car.Load("Assets/ship.spt");
}
void Car::Update([[maybe_unused]] double dt) {

    if (Engine::GetInput().KeyDown(CS230::Input::Keys::W)) {
        UpdatePosition(Math::RotationMatrix(GetRotation()) * Math::vec2{ 0,speed * dt });
    }
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::S)) {
        UpdatePosition(Math::RotationMatrix(GetRotation()) * Math::vec2{ 0,-speed * dt });
    }
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::A)) {
        UpdateRotation(rotation_speed * dt);
    }
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::D)) {
        UpdateRotation(-rotation_speed * dt);
    }
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left)) {
        UpdateRotation(0.5);
    }
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Right)) {
        UpdateRotation(-0.5);
    }
    
    UpdatePosition({ GetVelocity().x * dt, GetVelocity().y * dt });
    car_matrix = Math::TranslationMatrix(position) * Math::RotationMatrix(GetRotation());
    //car_matrix = Math::RotationMatrix(GetRotation()) * Math::TranslationMatrix(position) * Math::ScaleMatrix(scale);
}

void Car::Draw(Math::TransformationMatrix camera_matrix) {

    car.Draw(camera_matrix * GetMatrix());//draw the camera matrix based on the camera matrix
    //car.Draw(GetMatrix());// * camera_matrix
    camera_matrix;
    
}



