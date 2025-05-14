
/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode2.cpp
Project:    CS230 Engine
Author:     Junseok Lee
Created:    March 8, 2023
*/

#include "../Engine/Engine.h"
#include "States.h"
#include "Mode2.h"
#include "../Engine/Window.h"
#include "Meteor.h"

Mode2::Mode2()// how to get the static constexpr from window.h using Get size and Engine Get window?
{

}   

void Mode2::Load() {
    //gameobjectmanager.Add(new Meteor({  static_cast<double>(GetScreenWidth()), static_cast<double>(GetScreenHeight()) }));
    //gameobjectmanager.Add(new Meteor({  static_cast<double>(GetScreenWidth()), static_cast<double>(GetScreenHeight()) }));
    //gameobjectmanager.Add(new Meteor({  static_cast<double>(GetScreenWidth()), static_cast<double>(GetScreenHeight()) }));
    //gameobjectmanager.Add(new Meteor({  static_cast<double>(GetScreenWidth()), static_cast<double>(GetScreenHeight()) }));
    //gameobjectmanager.Add(new Meteor({  static_cast<double>(GetScreenWidth()), static_cast<double>(GetScreenHeight()) }));
    
    //ship.Load();
    camera.SetPosition({ 0,0 });
    ship_ptr = new Ship({ 0,0 });
    road_ptr = new Road({ 0,0 });
    gameobjectmanager.Add(road_ptr);
    gameobjectmanager.Add(ship_ptr);
}
void Mode2::Draw() {
    Engine::GetWindow().Clear(0x000000FF); // Clear the screen (e.g., to black)
    Math::vec2 screen_center = {
        static_cast<double>(Engine::GetWindow().GetSize().x / 2),
        static_cast<double>(Engine::GetWindow().GetSize().y / 2)
    };

    Math::TransformationMatrix translate_to_screen_center_matrix = Math::TranslationMatrix(screen_center);
    Math::TransformationMatrix inverse_ship_rotation_matrix = camera.Getoff1setMatrix(); // Provides Math::RotationMatrix(-ship_ptr->GetRotation())
    Math::TransformationMatrix translate_ship_to_origin_matrix = Math::TranslationMatrix(-ship_ptr->GetPosition());

    Math::TransformationMatrix pov_view_matrix =
        translate_to_screen_center_matrix *
        inverse_ship_rotation_matrix *
        translate_ship_to_origin_matrix;

    road_ptr->Draw(pov_view_matrix);

    ship_ptr->Draw(Math::TranslationMatrix(screen_center) * camera.GetoffsetMatrix());

}
    void Mode2::Update([[maybe_unused]] double dt) {

        camera.SetRotation(ship_ptr->GetRotation());


        gameobjectmanager.UpdateAll(dt);
        if (IsKeyPressed(KEY_TWO)) {
            //Engine::GetGameStateManager().ClearNextGameState();
            //Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Mode2));
            //Engine::GetLogger().LogEvent("ship position :");
        }
        if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::R)) {
            Engine::GetGameStateManager().ReloadState();
        }


    }

    void Mode2::Unload() {

    }

