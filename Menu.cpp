#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height)
{
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cout << "CRITICAL ERROR: Nie znaleziono czcionki arial.ttf!\n";
    }

    selectedItem = 0;
    std::string labels[3] = { "Nowa Gra", "Wczytaj gre", "Wyjscie" };

    for (int i = 0; i < 3; i++) {
        items[i].setFont(font);
        items[i].setString(labels[i]);
        items[i].setCharacterSize(40);
        items[i].setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);

        sf::FloatRect bounds = items[i].getLocalBounds();
        items[i].setOrigin(bounds.width / 2.f, bounds.height / 2.f);
        items[i].setPosition(width / 2.f, 200.f + i * 80.f);
    }
}

void Menu::draw(sf::RenderWindow& window) {
    for (auto& t : items) window.draw(t);
}

void Menu::moveUp() {
    if (selectedItem > 0) {
        items[selectedItem].setFillColor(sf::Color::White);
        selectedItem--;
        items[selectedItem].setFillColor(sf::Color::Red);
    }
}

void Menu::moveDown() {
    if (selectedItem < 2) { 
        items[selectedItem].setFillColor(sf::Color::White);
        selectedItem++;
        items[selectedItem].setFillColor(sf::Color::Red);
    }
}

int Menu::getSelectedItem() const {
    return selectedItem;
}