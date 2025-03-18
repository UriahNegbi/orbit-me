#include "Game.h"
#include <iostream>

void Game::initVariables()
{
    //vars
    window = nullptr;
    cameraMode = Free;
    simulator.planets = &objects;
    // game logic
    currentPlanetIndex = 0;
    speed = 5;
    orbitTrail = false;
    lockKeyPressed = false;
    leftKeyPressed = false;
    rightKeyPressed = false;
}

void Game::initRenderShapes()
{
    for (const Planet& planet : objects) {
        sf::CircleShape shape;
        shape.setPosition(static_cast<float>(planet.getPosition().x), static_cast<float>(planet.getPosition().y));
        shape.setRadius(static_cast<float>(planet.getRadius()));
        shape.setFillColor(planet.getColor());
        renderObjects.emplace_back(std::move(shape));
    }
}

void Game::initWindow()
{
    videoMode.height = 600;
    videoMode.width = 1000;
    window = new sf::RenderWindow(videoMode, "Gravity Simulator");
    window->setFramerateLimit(60);
}

void Game::initView()
{
    view.setSize(2000.f, 1000.f);
    view.setCenter(500.f, 300.f);
}

Game::Game()
{
    initVariables();
    initWindow();
    initUi();
    initRenderShapes();
    initView();
}

Game::~Game()
{
    delete window;
}

const bool Game::running() const
{
    return window->isOpen();
}

void Game::pollEvents()
{
    while (window->pollEvent(ev)) {
        ImGui::SFML::ProcessEvent(ev);
        switch (ev.type)
        {
        case sf::Event::Closed:
            window->close();
            break;

        case sf::Event::KeyPressed:
            if (ev.key.code == sf::Keyboard::Escape) {
                window->close();
            }
            if (ev.key.code == sf::Keyboard::Space) {
                if (simulator.getTimeStep() == 0) {
                    simulator.timeStep = simulator.tmpTimeStep;
                }
                else {
                    simulator.tmpTimeStep = simulator.timeStep;
                    simulator.timeStep = 0;
                }
            }
            if (ev.key.code == sf::Keyboard::G && !lockKeyPressed) {
                cameraMode = (cameraMode == Free) ? Lock : Free;
                lockKeyPressed = true;
            }
            if (ev.key.code == sf::Keyboard::Left && !leftKeyPressed) {
                if (currentPlanetIndex > 0) {
                    currentPlanetIndex--;
                }
                leftKeyPressed = true;
            }
            if (ev.key.code == sf::Keyboard::Right && !rightKeyPressed) {
                if (currentPlanetIndex < renderObjects.size() - 1) {
                    currentPlanetIndex++;
                }
                rightKeyPressed = true;
            }
            break;
        case sf::Event::KeyReleased:
            if (ev.key.code == sf::Keyboard::G) {
                lockKeyPressed = false;
            }
            if (ev.key.code == sf::Keyboard::Left) {
                leftKeyPressed = false;
            }
            if (ev.key.code == sf::Keyboard::Right) {
                rightKeyPressed = false;
            }
            break;
        }
    }
}

void Game::updatePlanet()
{
    for (size_t i = 0; i < objects.size(); ++i) {
        renderObjects[i].setPosition(static_cast<sf::Vector2f>(objects[i].getPosition()));

            orbitTrails[i].append(sf::Vertex(sf::Vector2f(objects[i].getPosition().x, objects[i].getPosition().y), objects[i].getColor()));

    }
}

void Game::updateCamera()
{
    if (cameraMode == Lock) {

        sf::Vector2f planetPos = renderObjects.at(currentPlanetIndex).getPosition();

        view.setCenter(planetPos.x, planetPos.y);
    }
}

void Game::addPlanet(Planet planet)
{
    objects.push_back(planet);

    // Create a new shape for the added planet
    sf::CircleShape shape;
    shape.setPosition(static_cast<float>(planet.getPosition().x), static_cast<float>(planet.getPosition().y));
    shape.setRadius(static_cast<float>(planet.getRadius()));
    shape.setFillColor(planet.getColor());
    renderObjects.emplace_back(std::move(shape));

    // Initialize the orbit trail for the new planet
    sf::VertexArray orbitTrail(sf::LinesStrip);
    orbitTrails.push_back(orbitTrail);
}

void Game::updateControls()
{
    if (cameraMode == Free) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            view.move(0.f, -speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            view.move(0.f, speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            view.move(speed, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            view.move(-speed, 0.f);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        view.zoom(0.7f); // Zoom in
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        view.zoom(2.f); // Zoom out
    }
}

void Game::update()
{
    pollEvents();
    simulator.computeGravity();
    updateControls();
    updatePlanet();
    updateCamera();
    updateUi();
}

void Game::renderPlanets()
{
    if (orbitTrail) {
        for (const auto& orbitTrail : orbitTrails) {
            window->draw(orbitTrail);
        }
    }
        for (const sf::CircleShape& renderObject : renderObjects) {
            window->draw(renderObject);
        }

}

void Game::render() {
    window->clear();
    window->setView(view);

    renderPlanets();
    renderUi();

    window->display();
}


void Game::setSpeed(float speed)
{
    this->speed = speed;
}

void Game::setOrbitMePath(std::string pathToOrbitMe)
{
    orbitMePath = pathToOrbitMe;
}

float Game::getSpeed() const
{
    return speed;
}
