#include "engine/engine.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum main_menu_options {
    PLAY,
    CHOOSE_MAP,
    SETTINGS,
    QUIT,
};

const std::string main_menu_strings[] = {"Play", "Choose Map", "Settings", "Quit"};

int main() {
    sf::RenderWindow window(sf::VideoMode(1280,720), "bhop_world", sf::Style::Titlebar);
    window.setPosition(sf::Vector2i(400, 150));

    bh::Game game(window);

    float dt;
    sf::Clock deltaClock;
    deltaClock.restart();

    bool main_menu_running = true;

    sf::Font menu_font;
    if (!menu_font.loadFromFile("res/Aroania.ttf")) {
        std::cout << "Error loading font: res/Aroania.ttf" << std::endl;
        return 1;
    }
    
    bh::Menu main_menu;
    int num_main_menu_options = sizeof(main_menu_strings)/sizeof(char*);
    
    for(int i = 0; i < num_main_menu_options; i++) {
        main_menu.add_button(
            bh::Button(
                sf::Text(main_menu_strings[i], menu_font), 
                sf::Vector2<float>(50, 50 + 30 * i)
            )
        );
    }

    while(window.isOpen()) {
        if (main_menu_running) {
            sf::Vector2<int> mouse_pos = sf::Mouse::getPosition(window);

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
    return 0; 
}
