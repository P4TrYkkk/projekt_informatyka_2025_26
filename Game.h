#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "paletka.h"
#include "pilka.h"
#include "brick.h"
#include "Menu.h"
#include "GameState.h"

enum class State { Menu, Playing, Paused };

class Game {
private:
    sf::RenderWindow m_window;

    Paletka m_paletka;
    Pilka m_pilka;
    std::vector<Brick> m_bricks;

    Menu m_menu;
    GameState m_gameState;
    State m_state;

    const float WIDTH = 800.f;
    const float HEIGHT = 600.f;

    void initBricks();
    void processEvents();
    void update(sf::Time dt);
    void render();

public:
    Game();
    void run();
};

#endif