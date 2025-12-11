#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <array>
#include <string>

class Menu {
private:
    int selectedItem;
    std::array<sf::Text, 3> items; 
    sf::Font font;

public:
    Menu(float width, float height);
    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedItem() const;
};

#endif