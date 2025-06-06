#pragma once
#include "../Engine/GamestateManager.h"
#include "../Engine/Font.h"
#include "../Game/Mode7.h"

#define GAMEOVER_TITLE_COLOR 0x33c45aFF          
#define GAMEOVER_SELECTED_ITEM_COLOR 0xFFFFFFFF  
#define GAMEOVER_SCORE_COLOR 0xAAAAAAFF
#define GAMEOVER_BACKGROUND_COLOR 0x222222FF     



class GameOver : public CS230::GameState {
public:
    GameOver();
    void Load() override;
    void Unload() override;
    void Update(double dt) override;
    void Draw() override;
    std::string GetName() override {
        return "GameOver";
    }

private:
    CS230::Texture* gameover_texture;
    CS230::Texture* score_texture;
};