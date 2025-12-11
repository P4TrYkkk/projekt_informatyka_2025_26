#ifndef PALETKA_H
#define PALETKA_H

#include <SFML/Graphics.hpp>

class Paletka {
private:
    sf::Vector2f pos;
    sf::Vector2f size;
    float speed;
    sf::RectangleShape shape;

public:
    Paletka(float x, float y, float w, float h, float spd)
        : pos(x, y), size(w, h), speed(spd)
    {
        shape.setSize(size);
        shape.setOrigin(size.x / 2.f, size.y / 2.f);
        shape.setPosition(pos);
        shape.setFillColor(sf::Color::Cyan);
    }

    void setPosition(sf::Vector2f newPos) {
        pos = newPos;
        shape.setPosition(pos);
    }

    void moveLeft(float dt) {
        pos.x -= speed * dt;
        shape.setPosition(pos);
    }

    void moveRight(float dt) {
        pos.x += speed * dt;
        shape.setPosition(pos);
    }

    void clampToBounds(float screenW) {
        if (pos.x - size.x / 2.f < 0) pos.x = size.x / 2.f;
        if (pos.x + size.x / 2.f > screenW) pos.x = screenW - size.x / 2.f;
        shape.setPosition(pos);
    }

    void draw(sf::RenderTarget& t) { t.draw(shape); }

    float getX() const { return pos.x; }
    float getY() const { return pos.y; }
    float getSzerokosc() const { return size.x; }
    float getWysokosc() const { return size.y; }

    sf::Vector2f getPosition() const { return pos; }
};

#endif