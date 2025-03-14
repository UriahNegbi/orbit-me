#pragma once // pragma once instead of ifdef 
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Planet.h"
#include "Simulator.h"

class Game
{
private:
    //vars
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;
    std::vector<sf::CircleShape> renderObjects;
    std::vector<sf::VertexArray> orbitTrails;
    std::vector<Planet> objects;
    sf::View view;

    // game logic
    enum CameraMode { Free, Lock };
    CameraMode cameraMode;
    size_t currentPlanetIndex;
    float speed;
    bool lockKeyPressed;
    bool leftKeyPressed;
    bool rightKeyPressed;
    // functions
    void initVariables();
    void initRenderShapes();
    void initWindow();
    void initView();
public:

    Game();
    ~Game();
    Simulator simulator;
    const bool running() const;
    bool orbitTrail;

    // functions
    void addPlanet(Planet planet);
    void pollEvents();

    void updatePlanet();
    void updateCamera();
    void updateControls();
    void update();
    
    void renderPlanets();
    void render();



    // setters
    void setSpeed(float speed); // the speed of the camera

    // getters
    float getSpeed() const;
};
