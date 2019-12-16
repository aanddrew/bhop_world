#pragma once

#include "GameSettings.h"
#include "Player.h"
#include "PlayerController.h"
#include "Map.h"

#include <SDL2/SDL.h>

namespace bh {
    
class Game {
public:
    Game(SDL_Window* window_in);
    static const GameSettings& get_settings();

    bool is_paused() const;
    void set_paused(bool paused_in);

    bool is_running() const;

    void update(float dt);
    void render();
private:
    Player player;
    PlayerController pc;
    Map map;

    SDL_Window* window;
    s3::Shader shader;

    static GameSettings settings;
    bool paused;
    bool running;
};

}
