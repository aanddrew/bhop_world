#ifndef MENU_H
#define MENU_H

#include "Button.h"
#include <SFML/Graphics.hpp>

namespace bh {
    
class Menu : public sf::Drawable {
public:
    Menu();
    void hover_mouse(sf::Vector2<int> mouse_pos);
    const Button* click_mouse(sf::Vector2<int> mouse_pos);

    void add_button(Button b);

    void draw(
        sf::RenderTarget& window, 
        sf::RenderStates states) const;
private:
    std::vector<Button> buttons;
};

}

#endif
