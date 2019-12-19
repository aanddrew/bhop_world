#include <iostream>

#include "engine/engine.h"
#include <stage3/Window.h>
#include <SDL2/SDL.h>

#include <chrono>

enum main_menu_options {
    PLAY,
    CHOOSE_MAP,
    SETTINGS,
    QUIT,
};

const std::string main_menu_strings[] = {"Play", "Choose Map", "Settings", "Quit"};

int main(int argc, char** argv) {
    s3::Window window("bhop_world", 1920, 1080);
    SDL_Window* sdl_window = window.getSDLWindow();

    bh::Game game(sdl_window);


    std::chrono::high_resolution_clock clock;
	auto lastTime = clock.now();

    bool running = true;
    SDL_Event e;

    float dt;

    int w,h;
    SDL_GetWindowSize(sdl_window, &w, &h);

    SDL_WarpMouseInWindow(sdl_window, w/2, h/2);

    while(game.is_running()) {
        int us = std::chrono::duration_cast<std::chrono::microseconds>(clock.now() - lastTime).count();
		lastTime = clock.now();
		//1,000,000 microseconds in a second
		dt = ((float)us)/1000000; //this is in seconds

        game.update(dt);

        window.clear();
        game.render();
        window.render();
    }
    return 0; 
}
