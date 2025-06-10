/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  mainmenu.cpp
Project:    CS230 Engine
Author:     Junseok Lee
Created:    March 8, 2023
*/
#include "MainMenu.h"
#include "../Engine/Engine.h"
#include "States.h"

MainMenu::MainMenu()
    : title_texture(nullptr),
    current_select(0),
    outdated_menu(true),
    counter(0.0)
{

}

void MainMenu::Load() {
    this->main_menu_texture = CS230::TextureManager().Load("Assets/Main_Menu.png");
    title_texture = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("CS230 Engine Test", MAINMENU_TITLE_COLOR);

    UpdateAllMenuItemTextures();
    TextureUpdate();
    outdated_menu = false;

    counter = 0.0;
    Engine::GetLogger().LogEvent("MainMenu Loaded");
}

void MainMenu::Update([[maybe_unused]] double dt) {
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Down)) {
        current_select = (current_select + 1) % SELECTOPTIONS;
        outdated_menu = true;
        Engine::GetLogger().LogEvent("Menu Down: Selected " + std::to_string(current_select));
    }
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Up)) {
        current_select = (current_select - 1 + SELECTOPTIONS) % SELECTOPTIONS;
        outdated_menu = true;
        Engine::GetLogger().LogEvent("Menu Up: Selected " + std::to_string(current_select));
    }

    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Enter)) {
        Engine::GetLogger().LogEvent("Menu Enter: Confirmed " + std::to_string(current_select));
        switch (current_select) {
        case 0:
            Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Gam150));
            break;
        case 1:
            Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Setting));
            break;
        case 2:

            Engine::GetGameStateManager().ClearNextGameState();
            break;
        }
    }

    if (outdated_menu) {
        UpdateAllMenuItemTextures();
        outdated_menu = false;
    }
    counter += dt;
    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::M)) {
        Mode7::high_score = 50;
    }
    TextureUpdate();
}
void MainMenu::Draw() {
    Engine::GetWindow().Clear(0x222222FF);
    main_menu_texture->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - main_menu_texture->GetSize()) / 2.0 }));

    Math::ivec2 window_size = Engine::GetWindow().GetSize();

    if (highscore) {
        highscore->Draw(Math::TranslationMatrix(Math::vec2{ 20.0f, 20.0f }));
    }

    //Math::ivec2 title_pos = { (window_size.x - title_texture->GetSize().x) / 2, window_size.y /2 };;
    //title_texture->Draw(Math::TranslationMatrix(title_pos));

    for (int i = 0; i < SELECTOPTIONS; ++i) {
        if (menu_tex[i]) {
            Math::ivec2 menu_pos = {
                (window_size.x - menu_tex[i]->GetSize().x) / 7,
                (window_size.y / 3) + (SELECTOPTIONS - 1 - i) * 60
            };
            menu_tex[i]->Draw(Math::TranslationMatrix(menu_pos));
        }
    }
}

void MainMenu::TextureUpdate()
{
    if (highscore) delete highscore;

    highscore = Engine::GetFont(static_cast<int>(Fonts::Outlined))
        .PrintToTexture("High Score : " + std::to_string(Mode7::high_score), 0xFFFFFFFF);
}


void MainMenu::UpdateMenuItemTexture(int index) {
    if (menu_tex[index]) {
        delete menu_tex[index];
        menu_tex[index] = nullptr;
    }

    std::string menu_item_text;
    switch (index) {
    case 0: menu_item_text = "Start"; break;
    case 1: menu_item_text = "Setting"; break;
    case 2: menu_item_text = "EXIT"; break;
    }

    unsigned int color = (index == current_select) ? MAINMENU_SELECTED_ITEM_COLOR : MAINMENU_UNSELECTED_ITEM_COLOR;

    menu_tex[index] = Engine::GetFont(static_cast<int>(Fonts::Outlined))
        .PrintToTexture(menu_item_text, color);

}

void MainMenu::UpdateAllMenuItemTextures() {
    for (int i = 0; i < SELECTOPTIONS; ++i) {
        UpdateMenuItemTexture(i);
    }
    Engine::GetLogger().LogEvent("All menu item textures updated.");
}

void MainMenu::Unload() {
    if (title_texture) {
        delete title_texture;
        title_texture = nullptr;
    }
    for (int i = 0; i < SELECTOPTIONS; ++i) {
        if (menu_tex[i]) {
            delete menu_tex[i];
            menu_tex[i] = nullptr;
        }
    }
    Engine::GetLogger().LogEvent("MainMenu Unloaded");
}