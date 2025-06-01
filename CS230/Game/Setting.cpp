#include "Setting.h"
#include "../Engine/Engine.h"
#include "States.h"
#include "Mode7.h"

Setting::Setting()
    : title_texture(nullptr),
    current_select(0),
    outdated_menu(true),
    counter(0.0)
{

}

void Setting::Load() {
    title_texture = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Setting", SETTING_TITLE_COLOR);

    UpdateAllMenuItemTextures();
    outdated_menu = false;

    counter = 0.0;
    Engine::GetLogger().LogEvent("MainMenu Loaded");
}

void Setting::Update([[maybe_unused]] double dt) {
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Down)) {
        current_select = (current_select + 1) % SELECTOPTIONSINSETTING;
        outdated_menu = true;
        Engine::GetLogger().LogEvent("Menu Down: Selected " + std::to_string(current_select));
    }
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Up)) {
        current_select = (current_select - 1 + SELECTOPTIONSINSETTING) % SELECTOPTIONSINSETTING;
        outdated_menu = true;
        Engine::GetLogger().LogEvent("Menu Up: Selected " + std::to_string(current_select));
    }

    if (current_select == 0) {
        if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Right)) {
            volume = std::min(volume + VOLUME_STEP, MAX_VOLUME);
            outdated_menu = true;
            Mode7::SetVolume(volume / 100.0f);
        }
        if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Left)) {
            volume = std::max(volume - VOLUME_STEP, MIN_VOLUME);
            outdated_menu = true;
            Mode7::SetVolume(volume / 100.0f);
        }
    }

    if (current_select == 1) {
        if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Right)) {
            current_difficulty = static_cast<Difficulty>(
                (static_cast<int>(current_difficulty) + 1) % 3);
            outdated_menu = true;
        }
        if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Left)) {
            current_difficulty = static_cast<Difficulty>(
                (static_cast<int>(current_difficulty) - 1 + 3) % 3);
            outdated_menu = true;
        }
    }

    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Enter)) {
        Engine::GetLogger().LogEvent("Menu Enter: Confirmed " + std::to_string(current_select));
        if (current_select == 2) {
            Engine::GetLogger().LogEvent("Setting next state to Mode2 (SpaceShooter)");
            Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
        }
    }
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Escape)) {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Gam150));
    }

    if (outdated_menu) {
        UpdateAllMenuItemTextures();
        outdated_menu = false;
    }


    counter += dt;
}
void Setting::Draw() {
    Engine::GetWindow().Clear(0x222222FF);

    Math::ivec2 window_size = Engine::GetWindow().GetSize();

    Math::ivec2 title_pos = { (window_size.x - title_texture->GetSize().x) / 2, window_size.y / 2 };;
    title_texture->Draw(Math::TranslationMatrix(title_pos));

    for (int i = 0; i < SELECTOPTIONSINSETTING; ++i) {
        if (menu_tex[i]) {
            Math::ivec2 menu_pos = {
                (window_size.x - menu_tex[i]->GetSize().x) / 2,
                (window_size.y / 4) + (SELECTOPTIONSINSETTING - 1 - i) * 60
            };
            menu_tex[i]->Draw(Math::TranslationMatrix(menu_pos));
        }
    }
}


void Setting::UpdateMenuItemTexture(int index) {
    if (menu_tex[index]) {
        delete menu_tex[index];
        menu_tex[index] = nullptr;
    }

    std::string menu_item_text;
    switch (index) {
    case 0: menu_item_text = "Volume: " + std::to_string(volume) + "%"; break;
    case 1: menu_item_text = "Difficulty: " + DifficultyToString(); break;
    case 2: menu_item_text = "MainMenu"; break;
    }

    unsigned int color = (index == current_select) ? SETTING_SELECTED_ITEM_COLOR : SETTING_UNSELECTED_ITEM_COLOR;

    menu_tex[index] = Engine::GetFont(static_cast<int>(Fonts::Outlined))
        .PrintToTexture(menu_item_text, color);

}

void Setting::UpdateAllMenuItemTextures() {
    for (int i = 0; i < SELECTOPTIONSINSETTING; ++i) {
        UpdateMenuItemTexture(i);
    }
    Engine::GetLogger().LogEvent("All menu item textures updated.");
}

void Setting::Unload() {
    if (title_texture) {
        delete title_texture;
        title_texture = nullptr;
    }
    for (int i = 0; i < SELECTOPTIONSINSETTING; ++i) {
        if (menu_tex[i]) {
            delete menu_tex[i];
            menu_tex[i] = nullptr;
        }
    }
    Engine::GetLogger().LogEvent("MainMenu Unloaded");
}

std::string Setting::DifficultyToString() const {
    switch (current_difficulty) {
    case Difficulty::Easy: return "Easy";
    case Difficulty::Normal: return "Normal";
    case Difficulty::Hard: return "Hard";
    default: return "Unknown";
    }
}