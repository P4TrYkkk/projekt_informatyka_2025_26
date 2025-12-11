#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include "paletka.h"
#include "pilka.h"
#include "brick.h"

struct BlockData {
    float x, y;
    int hp;
};

class GameState {
private:
    sf::Vector2f paddlePos;
    sf::Vector2f ballPos;
    sf::Vector2f ballVel;
    std::vector<BlockData> blocksData;

public:
    void capture(const Paletka& p, const Pilka& b, const std::vector<Brick>& bricks) {
        paddlePos = p.getPosition();
        ballPos = b.getPosition();
        ballVel = b.getVelocity();

        blocksData.clear();
        for (const auto& brick : bricks) {
            if (!brick.isDestroyed()) {
                blocksData.push_back({ brick.getPosition().x, brick.getPosition().y, brick.getHP() });
            }
        }
    }

    void apply(Paletka& p, Pilka& b, std::vector<Brick>& bricks) {
        p.setPosition(paddlePos);
        b.reset(ballPos, ballVel);

        bricks.clear();
        float bw = 74.f;
        float bh = 25.f;

        for (const auto& data : blocksData) {
            bricks.emplace_back(sf::Vector2f(data.x, data.y), sf::Vector2f(bw, bh), data.hp);
        }
    }

    bool saveToFile(const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) return false;

        file << paddlePos.x << " " << paddlePos.y << "\n";
        file << ballPos.x << " " << ballPos.y << " " << ballVel.x << " " << ballVel.y << "\n";

        file << blocksData.size() << "\n";
        for (const auto& bd : blocksData) {
            file << bd.x << " " << bd.y << " " << bd.hp << "\n";
        }
        file.close();
        return true;
    }

    bool loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) return false;

        file >> paddlePos.x >> paddlePos.y;
        file >> ballPos.x >> ballPos.y >> ballVel.x >> ballVel.y;

        int count;
        file >> count;
        blocksData.clear();
        for (int i = 0; i < count; i++) {
            float x, y;
            int hp;
            file >> x >> y >> hp;
            blocksData.push_back({ x, y, hp });
        }
        file.close();
        return true;
    }
};

#endif