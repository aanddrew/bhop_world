#pragma once

#include <string>
#include <SDL2/SDL.h>

namespace bh {

struct GameSettings {
    float max_speed;
    float air_acceleration;
    float ground_acceleration;
    float gravity;

    SDL_Keycode forward_key;
    SDL_Keycode backward_key;
    SDL_Keycode right_key;
    SDL_Keycode left_key;
    SDL_Keycode jump_key;
    SDL_Keycode walk_key;
};

void load_settings_from_file(const std::string& file_name, GameSettings& settings);

GameSettings load_default_settings();

}
