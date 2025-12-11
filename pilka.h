#ifndef PILKA_H
#define PILKA_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#include "paletka.h"
#include "brick.h"

class Pilka {
private:
    sf::Vector2f pos;
    sf::Vector2f vel;
    float radius;
    sf::CircleShape shape;

public:
    Pilka(float x, float y, float vx, float vy, float r)
        : pos(x, y), vel(vx, vy), radius(r)
    {
        shape.setRadius(radius);
        shape.setOrigin(radius, radius);
        shape.setFillColor(sf::Color::White);
        shape.setPosition(pos);
    }

    void reset(sf::Vector2f newPos, sf::Vector2f newVel) {
        pos = newPos;
        vel = newVel;
        shape.setPosition(pos);
    }

    sf::Vector2f getPosition() const { return pos; }
    sf::Vector2f getVelocity() const { return vel; }

    void move(float dt)
    {
        pos.x += vel.x * dt;
        pos.y += vel.y * dt;
        shape.setPosition(pos);
    }

    void bounceX() { vel.x = -vel.x; }
    void bounceY() { vel.y = -vel.y; }

    bool checkCollisionsWithWalls(float width, float height)
    {
        if (pos.x - radius <= 0) { pos.x = radius; bounceX(); }
        else if (pos.x + radius >= width) { pos.x = width - radius; bounceX(); }

        if (pos.y - radius <= 0) { pos.y = radius; bounceY(); }

        if (pos.y - radius > height) return true;

        shape.setPosition(pos);
        return false;
    }

    bool collidePaddle(const Paletka& p)
    {
        float px = p.getX();
        float py = p.getY();
        float pw = p.getSzerokosc();
        float ph = p.getWysokosc();

        if (pos.x >= px - pw / 2.f && pos.x <= px + pw / 2.f &&
            pos.y + radius >= py - ph / 2.f && pos.y - radius < py + ph / 2.f)
        {
            vel.y = -std::abs(vel.y);
            pos.y = py - ph / 2.f - radius;
            shape.setPosition(pos);
            return true;
        }
        return false;
    }

    bool collideBricks(std::vector<Brick>& bricks)
    {
        bool hitAny = false;

        for (auto& b : bricks)
        {
            if (b.isDestroyed()) continue;

            if (shape.getGlobalBounds().intersects(b.getGlobalBounds()))
            {
                b.hit();
                hitAny = true;
            }
        }

        if (hitAny) {
            bounceY();
            return true;
        }

        return false;
    }

    void draw(sf::RenderTarget& t) { t.draw(shape); }
};

#endif