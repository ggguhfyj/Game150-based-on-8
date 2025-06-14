#include "GameOver.h"
#include "../Engine/Engine.h"
#include "States.h"

GameOver::GameOver()
{
}

void GameOver::Load()
{
    gameover_texture = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Game Over", GAMEOVER_TITLE_COLOR);
    score_texture = Engine::GetFont(static_cast<int>(Fonts::Simple)).PrintToTexture("Score: " + std::to_string(score), GAMEOVER_SCORE_COLOR);
}

void GameOver::Unload()
{
    delete gameover_texture;
    delete score_texture;
}

void GameOver::Update([[maybe_unused]] double dt)
{
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Enter)) {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
    }
}

void GameOver::Draw()
{
    Engine::GetWindow().Clear(0x00000000);

    Math::ivec2 window_size = Engine::GetWindow().GetSize();

    Math::ivec2 gameover_pos = { (window_size.x - gameover_texture->GetSize().x) / 2, window_size.y / 2 };;
    Math::ivec2 score_pos = { (window_size.x - gameover_texture->GetSize().x) / 2, window_size.y / 4 };;
    gameover_texture->Draw(Math::TranslationMatrix(gameover_pos));
    score_texture->Draw(Math::TranslationMatrix(score_pos));
}