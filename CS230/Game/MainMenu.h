/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  mainmenu.h
Project:    CS230 Engine
Author:     Junseok Lee
Created:    March 8, 2023
*/

#pragma once
#include "../Engine/GameState.h"
#include "../Engine/Texture.h"




#define SELECTOPTIONS 4



#define MAINMENU_TITLE_COLOR 0x33c45aFF          
#define MAINMENU_SELECTED_ITEM_COLOR 0xFFFFFFFF  
#define MAINMENU_UNSELECTED_ITEM_COLOR 0xAAAAAAFF
#define MAINMENU_BACKGROUND_COLOR 0x222222FF     

class MainMenu : public CS230::GameState {
public:
    MainMenu();
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;
    std::string GetName() override {
        return "MainMenu";
    }

private: 
    void UpdateMenuItemTexture(int index);
    void UpdateAllMenuItemTextures();

public: 
    double counter = 0; 
    CS230::Texture* title_texture;
    int current_select; 
    CS230::Texture* menu_tex[SELECTOPTIONS];
    bool outdated_menu; 
};