#pragma once
#include "../Engine/GameState.h"
#include "../Engine/Texture.h"

#define SELECTOPTIONSINSETTING 4
#define SETTING_TITLE_COLOR 0xFF2233FF          
#define SETTING_SELECTED_ITEM_COLOR 0xFFFFFFFF  
#define SETTING_UNSELECTED_ITEM_COLOR 0xFFFFAAFF
#define MIN_VOLUME 0
#define MAX_VOLUME 100
#define VOLUME_STEP 10

enum class Difficulty { Easy, Normal, Hard, special };

class Setting : public CS230::GameState {
public:
    Setting();
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    std::string DifficultyToString() const;
    void Draw() override;
    std::string GetName() override {
        return "Setting";
    }

private:
    void UpdateMenuItemTexture(int index);
    void UpdateAllMenuItemTextures();

    Difficulty current_difficulty = Difficulty::Normal;
public:
    double counter = 0;
    bool special_open = false;
    CS230::Texture* title_texture;
    int current_select;
    CS230::Texture* menu_tex[SELECTOPTIONSINSETTING];
    bool outdated_menu;
    int volume = 100;
};