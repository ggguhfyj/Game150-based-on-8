/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Splash.h
Project:    CS230 Engine
Author:     Junseok Lee
Created:    March 15, 2025
*/

#pragma once
#include "../Engine/GameState.h"
#include "raylib.h"
#include "../Engine/Sprite.h"
#include "../Game/Ship.h"
#include "..\Engine\GameObjectManager.h"
#include "..\Game\Road.h"
#include "..\Engine\Camera.h"

class Mode2 : public CS230::GameState {
public:
    Mode2();
    void Load() override;
    void Update([[maybe_unused]] double dt) override;
    void Unload() override;

    void Draw() override;
    std::string GetName() override {
        return "Mode2";
    }

public:


public:
    CS230::GameObjectManager gameobjectmanager;
    CS230::Camera camera;
    Ship* ship_ptr;
    Road* road_ptr;
    CS230::Window window;

    static constexpr double SHIP_SPEED = 300.0;
    //Math::vec2 ship_position;
    //CS230::Sprite ship;
};
