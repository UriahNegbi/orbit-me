// Simulator.h
#pragma once 

#include <SFML/Graphics.hpp>
#include <vector>
#include "Planet.h"
#include <functional>
#include <iostream>

class Simulator
{
    friend class Game;
public:
    Simulator& operator=(Simulator&& sim) = default;
    // Constructor: Takes a vector of planets, gravitational constant, and time step
    Simulator(std::vector<Planet>& planets, double gravitationalConstant, double deltaTime);
    Simulator() = default;

    // Compute gravitational force between all planets and update their velocities and positions
    void computeGravity();
    double computeSlingshotEffect(const sf::Vector2<double>& relativeVelocity, const Planet& planetB);
    // Getters
    double getTimeStep();
    double getTimeStepTmp();
    inline double getG() { return G; };

    std::vector<Planet>* planets;   // List of planets in the simulation
    double G;
    double timeStep;               // Time step for the simulation
    double tmpTimeStep = NULL;     // Saving the last time step
};
