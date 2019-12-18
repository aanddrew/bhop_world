#include "Button.h"

namespace bh {

Button::Button() {
    
}

/*

Button::Button(sf::Text text_in, const sf::Vector2<float> pos)
: text(text_in) {
    text.setPosition(pos);
    text.setFillColor(sf::Color::White);
}

void Button::hover_mouse(sf::Vector2<int> mouse_pos) {
    sf::Vector2<float> float_mouse(mouse_pos.x, mouse_pos.y);
    if (text.getGlobalBounds().contains(float_mouse)) {
        text.setFillColor(sf::Color::Red);
    }
    else {
        text.setFillColor(sf::Color::White);
    }
}

bool Button::click_mouse(sf::Vector2<int> mouse_pos) {
    sf::Vector2<float> float_mouse(mouse_pos.x, mouse_pos.y);
    return text.getGlobalBounds().contains(float_mouse);
}

std::string Button::get_string() const {
    return text.getString().toAnsiString();
}

void Button::draw(
        sf::RenderTarget& window, 
        sf::RenderStates states) const {
    window.draw(text);
}

*/

}
