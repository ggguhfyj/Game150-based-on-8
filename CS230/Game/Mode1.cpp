/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode1.cpp
Project:    CS230 Engine
Author:     Junseok Lee
Created:    March 11, 2025
Updated:        March 23, 2025
*/

#include "../Engine/Engine.h"
#include "States.h"
#include "Mode1.h"
#include "Cat.h"
#include "Asteroid.h"


Mode1::Mode1() :
  
    camera({ { 0.15 * Engine::GetWindow().GetSize().x, 0 }, { 0.15 * Engine::GetWindow().GetSize().x, 0 } })//player zone
{

}

void Mode1::update_timer_text(int value) {
    timer_texture = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Timer: " + std::to_string(value), 0xFFFFFFFF);
}

void Mode1::Load() {
    

    background.Add("Assets/Planets.png", 0.25);
    background.Add("Assets/Ships.png", 0.5);
    background.Add("Assets/Foreground.png", 1);

    
    cat_ptr = new Cat({ 300, floor }, camera);
    gameobjectmanager.Add(cat_ptr);
    gameobjectmanager.Add(new Asteroid({ 600, floor }));
    gameobjectmanager.Add(new Asteroid({ 1800, floor }));
    gameobjectmanager.Add(new Asteroid({ 2400, floor }));

    gameobjectmanager.Add(new Crates({ 900, floor }, 2));
    gameobjectmanager.Add(new Crates({ 1400, floor }, 1));
    gameobjectmanager.Add(new Crates({ 2000, floor }, 5));
    gameobjectmanager.Add(new Crates({ 4000, floor }, 3));
    gameobjectmanager.Add(new Crates({ 5600, floor }, 5));

    gameobjectmanager.Add(new Robot({ 1200, Mode1::floor }));
    gameobjectmanager.Add(new Robot({ 2200, Mode1::floor }));
    gameobjectmanager.Add(new Robot({ 3400, Mode1::floor }));
    gameobjectmanager.Add(new Robot({ 4200, Mode1::floor }));


    camera.SetPosition({ 0,0 });
    camera.SetLimit({ { 0,0 }, { background.GetSize().x - Engine::GetWindow().GetSize().x, background.GetSize().y - Engine::GetWindow().GetSize().y } });
    //program stops responding here
    timer = timer_max;
    last_timer = static_cast<int>(timer_max);
    update_timer_text(last_timer);

}

void Mode1::Update([[maybe_unused]] double dt) {
    gameobjectmanager.UpdateAll(dt);

    camera.Update(cat_ptr->GetPosition());
    Engine::GetLogger().LogEvent(std::to_string(camera.GetPosition().x) + " , " + std::to_string(camera.GetPosition().y) + "\n");

    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Enter)) {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Mode2));
    }
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::R)) {
        Engine::GetGameStateManager().ReloadState();
    }

    timer -= dt;
    if (static_cast<int>(timer) < last_timer) {
        last_timer = static_cast<int>(timer);
        update_timer_text(last_timer);
    }
    if (last_timer == 0) {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Splash));
    }

}

void Mode1::Draw() {
    Engine::GetWindow().Clear(0x000000FF);
    background.Draw(camera);
    gameobjectmanager.DrawAll(camera.GetMatrix());
    timer_texture->Draw(Math::TranslationMatrix(Math::ivec2{ CS230::Window().GetSize().x - 10 - timer_texture->GetSize().x, CS230::Window().GetSize().y - timer_texture->GetSize().y - 5}));

}




void Mode1::Unload() {
    background.Unload();
    gameobjectmanager.Unload();
    cat_ptr = nullptr;
}
