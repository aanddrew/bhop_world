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

int main() {
    //sf::RenderWindow window(sf::VideoMode(1280,720), "bhop_world", sf::Style::Titlebar);
    //window.setPosition(sf::Vector2i(400, 150));

    //bh::Game game(window);

    //float dt;
    //deltaClock.restart();

    //bool main_menu_running = true;

    //bh::Menu main_menu;
    //int num_main_menu_options = sizeof(main_menu_strings)/sizeof(char*);
    //
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
        /*
        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
                case SDL_QUIT:
                    running = false;
                break;
            }
        }
        */

        int us = std::chrono::duration_cast<std::chrono::microseconds>(clock.now() - lastTime).count();
		lastTime = clock.now();
		//1,000,000 microseconds in a second
		dt = ((float)us)/1000000; //this is in seconds

        game.update(dt);

        window.clear();
        game.render();
        window.render();
    }

    /*
    while(window.isOpen()) {
        if (main_menu_running) {
            sf::Event event;
            const bh::Button* clicked_button = nullptr;

            while(window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return 0;
                }
                else if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Button::Left) {
                        clicked_button = main_menu.click_mouse(sf::Vector2<int>(event.mouseButton.x, event.mouseButton.y));
                    }
                }
            }

            if (clicked_button != nullptr) {
                if (clicked_button->get_string() == main_menu_strings[PLAY]) {
                    game.set_paused(false);
                    main_menu_running = false;
                }
                else if (clicked_button->get_string() == main_menu_strings[QUIT]) {
                    window.close();
                    return 0;
                }
            }

            window.clear();
            
            main_menu.hover_mouse(mouse_pos);
            window.draw(main_menu);

            window.display();

            continue;
        }
        dt = deltaClock.restart().asSeconds();
        //std::cout << "fps: " << 1.0/dt.asSeconds() << std::endl;
        if (!game.is_paused()) {
            game.update(dt);
            window.clear();
            game.render();
            window.display();
        }
        else {
            main_menu_running = true;
            //window.close();
        }
    } 
    */
    return 0; 
}
