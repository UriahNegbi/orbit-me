#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Planet.h"
#include "Simulator.h"
#include <imgui.h>
#include <imgui-SFML.h>

class Game
{
private:
    // Variables
    std::string orbitMePath; // Path to the lab
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;
    std::vector<sf::CircleShape> renderObjects;
    std::vector<sf::VertexArray> orbitTrails;
    std::vector<Planet> objects;
    sf::View view;
    // ui stuff
    void simulationSettingsUi();
    void addPlanetUi();
    // Game logic
    enum CameraMode { Free, Lock };
    CameraMode cameraMode;
    size_t currentPlanetIndex;
    float speed;
    bool lockKeyPressed;
    bool leftKeyPressed;
    bool rightKeyPressed;

    // Functions
    void initVariables();
    void initRenderShapes();
    void initWindow();
    void initUi();
    void initView();

public:
    Game();
    ~Game();
    Simulator simulator;
    const bool running() const;
    bool orbitTrail;

    // Functions
    void addPlanet(Planet planet);
    void pollEvents();
    void updateUi();
    void updatePlanet();
    void updateCamera();
    void updateControls();
    void update();
    void renderUi();
    void renderPlanets();
    void render();

    // Setters and getters
    void setSpeed(float speed);
    void setOrbitMePath(std::string pathToOrbitMe);
    float getSpeed() const;
};
