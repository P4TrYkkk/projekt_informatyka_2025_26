#ifndef BRICK_H
#define BRICK_H

#include <SFML/Graphics.hpp>

class Brick : public sf::RectangleShape {
private:
    int life;

public:
    Brick(sf::Vector2f position, sf::Vector2f size, int hp) : life(hp) {
        setPosition(position);
        setSize(size);
        setOutlineThickness(1.f);
        setOutlineColor(sf::Color::Black);
        updateColor();
    }

    int getHP() const { return life; }

    void hit() {
        if (life > 0) {
            life--;
            updateColor();
        }
    }

    bool isDestroyed() const {
        return life <= 0;
    }

    void updateColor() {
        if (life >= 3) setFillColor(sf::Color::Red);
        else if (life == 2) setFillColor(sf::Color::Yellow);
        else if (life == 1) setFillColor(sf::Color::Green);
        else setFillColor(sf::Color::Transparent);
    }
};

#endif