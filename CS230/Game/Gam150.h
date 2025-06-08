/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  gam150.h
Project:    CS230 Engine
Author:     Junseok Lee
Created:    March 11, 2025
Updated:    March 23, 2025
*/

#pragma once
#include <vector>
#include "..\Engine\GameObjectManager.h"
#include "..\Engine\TextureManager.h"
#include "../Engine/GameState.h"
#include "../Engine/Texture.h"
#include "../Engine/Sprite.h"
#include "../Engine/Vec2.h"
#include "..\Game\Mode7.h"
#include "background.h"
#include "newmapGen.h"
#include "Road.h"
#include "Car.h"

class Gam150 : public CS230::GameState {
public:
    Gam150();
    void Load() override;
    void Update([[maybe_unused]] double dt) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override {
        return "Gam150";
    }
  


private:


    enum DrawMode
    {
        normal,
        mode7

    };
    RenderTexture2D target;
    Shader fish;
    Shader scanlines;
    Shader downhillShader; // <--- Add this
    float hillFactor;
    int drawmode = 1;
    CS230::Texture* timer_texture; // default constructor errors
    double timer;
    int last_timer;
};