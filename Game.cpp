#include "Game.h"
#include <iostream>

Game::Game()
    : m_window(sf::VideoMode(800, 600), "Arkanoid"),
    m_paletka(400.f, 550.f, 120.f, 20.f, 600.f),
    m_pilka(400.f, 400.f, 250.f, -250.f, 8.f),
    m_menu(800.f, 600.f),
    m_state(State::Menu)
{
    m_window.setFramerateLimit(60);
    initBricks();
}

void Game::initBricks()
{
    const int COLS = 10;
    const int ROWS = 4;
    float spacing = 5.f;
    float sideMargin = 10.f;
    float bh = 25.f;
    float availableWidth = WIDTH - (2 * sideMargin) - ((COLS - 1) * spacing);
    float bw = availableWidth / COLS;

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            float x = sideMargin + c * (bw + spacing);
            float y = 70.f + r * (bh + spacing);
            m_bricks.emplace_back(sf::Vector2f(x, y), sf::Vector2f(bw, bh), 3);
        }
    }
}

void Game::run()
{
    sf::Clock clock;
    while (m_window.isOpen())
    {
        processEvents();
        sf::Time dt = clock.restart();

        if (m_state == State::Playing) {
            update(dt);
        }

        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_window.close();

        // 1. MENU
        if (m_state == State::Menu && event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Up) m_menu.moveUp();
            if (event.key.code == sf::Keyboard::Down) m_menu.moveDown();
            if (event.key.code == sf::Keyboard::Enter)
            {
                int sel = m_menu.getSelectedItem();

                if (sel == 0) { // Nowa gra
                    m_paletka = Paletka(400.f, 550.f, 120.f, 20.f, 600.f);
                    m_pilka = Pilka(400.f, 400.f, 250.f, -250.f, 8.f);
                    initBricks();
                    m_state = State::Playing;
                }
                else if (sel == 1) { // Wczytaj gre
                    if (m_gameState.loadFromFile("save.txt")) {
                        m_gameState.apply(m_paletka, m_pilka, m_bricks);
                        m_state = State::Paused;
                        std::cout << "Wczytano gre!" << std::endl;
                    }
                }
                else if (sel == 2) { // Wyjscie
                    m_window.close();
                }
            }
        }

        // 2. PODCZAS GRY / PAUZY
        if (m_state == State::Playing || m_state == State::Paused)
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    m_state = State::Menu;

                // P - Pauza
                if (event.key.code == sf::Keyboard::P)
                {
                    if (m_state == State::Playing) m_state = State::Paused;
                    else m_state = State::Playing;
                }

                // S - Zapisz
                if (event.key.code == sf::Keyboard::S)
                {
                    m_gameState.capture(m_paletka, m_pilka, m_bricks);
                    if (m_gameState.saveToFile("save.txt"))
                        std::cout << "Zapisano gre!" << std::endl;
                }

                // L - Wczytaj
                if (event.key.code == sf::Keyboard::L)
                {
                    if (m_gameState.loadFromFile("save.txt")) {
                        m_gameState.apply(m_paletka, m_pilka, m_bricks);
                        m_state = State::Paused;
                        std::cout << "Wczytano gre!" << std::endl;
                    }
                }
            }
        }
    }
}

void Game::update(sf::Time dt)
{
    float time = dt.asSeconds();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) m_paletka.moveLeft(time);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) m_paletka.moveRight(time);
    m_paletka.clampToBounds(WIDTH);

    m_pilka.move(time);

    if (m_pilka.checkCollisionsWithWalls(WIDTH, HEIGHT)) {
        m_state = State::Menu;
    }

    m_pilka.collidePaddle(m_paletka);
    m_pilka.collideBricks(m_bricks);
}

void Game::render()
{
    m_window.clear(sf::Color(50, 50, 50));

    if (m_state == State::Menu) {
        m_menu.draw(m_window);
    }
    else {
        m_paletka.draw(m_window);
        m_pilka.draw(m_window);
        for (auto& b : m_bricks)
            if (!b.isDestroyed()) m_window.draw(b);
    }

    m_window.display();
}