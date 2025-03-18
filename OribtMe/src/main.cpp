#include "Game.h"
#include <random>
#include <cmath>

int main()
{
    Game game;

    // Gravitational constant in appropriate units
    game.setSpeed(10.f);
    const double G = 6.67430e-11;
    const double sunMass = 1.989e30;

    // Add Sun (yellow, large, stationary)
    game.addPlanet(Planet(20.f, sf::Color(255, 204, 0), sf::Vector2<double>(0.0, 0.0), sf::Vector2<double>(0, 0), sunMass));

    // Add Earth (blue-green) for testing slingshot
    double earthDistance = 150.0;
    double earthVelocity = std::sqrt(G * sunMass / earthDistance);
    game.addPlanet(Planet(6.f, sf::Color(0, 100, 255), sf::Vector2<double>(earthDistance, 0.0), sf::Vector2<double>(0, earthVelocity), 5.972e24));

    // Add Jupiter (orange) to provide the slingshot assist
    double jupiterDistance = 780.0;
    double jupiterVelocity = std::sqrt(G * sunMass / jupiterDistance);
    game.addPlanet(Planet(20.f, sf::Color(255, 165, 0), sf::Vector2<double>(jupiterDistance, 0.0), sf::Vector2<double>(0, jupiterVelocity), 1.898e27));

    // Update Simulator vars
    game.orbitTrail = true;
    game.simulator.G = G;
    game.simulator.timeStep = 0.000000001;

    // Main game loop
    while (game.running()) {
        game.pollEvents();
        game.update();
        game.render();
        }

        return 0;
    }



