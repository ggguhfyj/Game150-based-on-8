/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Window.h
Project:    CS230 Engine
Author:     Junseok Lee
Created:    March 11, 2025
Updated:    March 23, 2025
*/

#pragma once
#include <string>
#include <raylib.h>
#include <rlgl.h>
#include "Vec2.h"

namespace CS230 {
    class Window {
    public:
        void Start(std::string title);
        void Update();
        bool IsClosed() const;
        Math::ivec2 GetSize() const;
        void Clear(unsigned int color);
        
    private:
        Math::ivec2 size;
        static constexpr int default_width = 1200;
        static constexpr int default_height = 780;
        static constexpr unsigned int default_background = UINT_MAX;
    };
}
