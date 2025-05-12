/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Engine.h
Project:    CS230 Engine
Author:     Junseok Lee
Created:    March 11, 2025
Updated:    March 18, 2025
*/

#pragma once

#include "Logger.h"
#include "Window.h"
#include "GameStateManager.h"
#include "Input.h"
#include "TextureManager.h"
#include <chrono>
#include "Font.h"
#include "Fonts.h"

class Engine {
public:
    static Engine& Instance() { // instance is a function that returns a static engine instance. 
        static Engine instance;
        return instance;
    }

    static CS230::Logger& GetLogger() {
        return Instance().logger;
    }

    static CS230::Window& GetWindow() {
        return Instance().window;
    }

    static CS230::GameStateManager& GetGameStateManager() {
        return Instance().gamestatemanager;
    }

    static CS230::Input& GetInput() {
        return Instance().input;
    }
    static CS230::TextureManager& GetTextureManager()
    {
        return Instance().texturemanager;
    }

    static CS230::Font& GetFont(int index)
    {
        return Instance().fonts[index];
    }

    void AddFont(const std::filesystem::path& file_name)
    {
        fonts.push_back(CS230::Font(file_name)); // Construct a temporary CS230::Font and pass it
    }

    void Start(std::string window_title);
    void Stop();
    void Update();

    bool HasGameEnded() {
        return  (window.IsClosed()) || gamestatemanager.HasGameEnded();
    }

private:
    Engine();
    std::chrono::system_clock::time_point last_tick;
    std::chrono::system_clock::time_point last_test;
    
    CS230::Logger logger;
    CS230::Window window;
    CS230::GameStateManager gamestatemanager;
    CS230::Input input;
    CS230::TextureManager texturemanager;
    
    std::vector<CS230::Font> fonts;
    int frame_count = 0;

    static constexpr double TargetFPS = 30.0;
    static constexpr int FPSDuration = 5;
    static constexpr int FPSTargetFrames = static_cast<int>(FPSDuration * TargetFPS);
};
