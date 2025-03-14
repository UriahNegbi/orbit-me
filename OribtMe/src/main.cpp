#include "Game.h"




int main()
{
    Game game;
    // Gravitational constant in appropriate units
    game.setSpeed(10.f);
    const double G = 6.67430e-11;
    const double sunMass = 1.989e30;

    // Sun (yellow, large, stationary)
    game.addPlanet(Planet(20.f, sf::Color(255, 204, 0), sf::Vector2<double>(0.0, 0.0), sf::Vector2<double>(0, 0), sunMass));

    // Mercury (gray)
    double mercuryDistance = 60.0;
    double mercuryVelocity = std::sqrt(G * sunMass / mercuryDistance);
    game.addPlanet(Planet(2.f, sf::Color(169, 169, 169), sf::Vector2<double>(mercuryDistance, 0.0), sf::Vector2<double>(0, mercuryVelocity), 3.301e23));

    // Venus (light yellow)
    double venusDistance = 110.0;
    double venusVelocity = std::sqrt(G * sunMass / venusDistance);
    game.addPlanet(Planet(6.f, sf::Color(255, 223, 0), sf::Vector2<double>(venusDistance, 0.0), sf::Vector2<double>(0, venusVelocity), 4.867e24));

    // Earth (blue-green)
    double earthDistance = 150.0;
    double earthVelocity = std::sqrt(G * sunMass / earthDistance);
    game.addPlanet(Planet(6.f, sf::Color(0, 100, 255), sf::Vector2<double>(earthDistance, 0.0), sf::Vector2<double>(0, earthVelocity), 5.972e24));

    // Mars (red)
    double marsDistance = 230.0;
    double marsVelocity = std::sqrt(G * sunMass / marsDistance);
    game.addPlanet(Planet(3.f, sf::Color(255, 0, 0), sf::Vector2<double>(marsDistance, 0.0), sf::Vector2<double>(0, marsVelocity), 6.417e23));

    // Jupiter (orange)
    double jupiterDistance = 780.0;
    double jupiterVelocity = std::sqrt(G * sunMass / jupiterDistance);
    game.addPlanet(Planet(20.f, sf::Color(255, 165, 0), sf::Vector2<double>(jupiterDistance, 0.0), sf::Vector2<double>(0, jupiterVelocity), 1.898e27));

    // Saturn (pale yellow)
    double saturnDistance = 1400.0;
    double saturnVelocity = std::sqrt(G * sunMass / saturnDistance);
    game.addPlanet(Planet(17.f, sf::Color(210, 180, 140), sf::Vector2<double>(saturnDistance, 0.0), sf::Vector2<double>(0, saturnVelocity), 5.683e26));

    // Uranus (light blue)
    double uranusDistance = 2800.0;
    double uranusVelocity = std::sqrt(G * sunMass / uranusDistance);
    game.addPlanet(Planet(10.f, sf::Color(173, 216, 230), sf::Vector2<double>(uranusDistance, 0.0), sf::Vector2<double>(0, uranusVelocity), 8.681e25));

    // Neptune (deep blue)
    double neptuneDistance = 4500.0;
    double neptuneVelocity = std::sqrt(G * sunMass / neptuneDistance);
    game.addPlanet(Planet(10.f, sf::Color(0, 0, 139), sf::Vector2<double>(neptuneDistance, 0.0), sf::Vector2<double>(0, neptuneVelocity), 1.024e26));

    // update Simulator vars
    game.simulator.G = G;
    game.simulator.timeStep = 0.000000001;
    game.simulator.planets = &game.objects;

    while (game.running())
    {
        game.pollEvents();
        game.update();
        game.render();
    }

    return 0;
}