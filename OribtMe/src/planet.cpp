#include "Planet.h"
#include <cmath>

// Constructor
Planet::Planet(float r, sf::Color col, sf::Vector2<double> pos, sf::Vector2<double> vel, double m)
    : radius(r), color(col), position(pos), velocity(vel), mass(m) {}

// Getters
double Planet::getRadius() const { return radius; }
sf::Color Planet::getColor() const { return color; }
sf::Vector2<double> Planet::getPosition() const { return position; }
sf::Vector2<double> Planet::getVelocity() const { return velocity; }
double Planet::getMass() const { return mass; }

// Setters
void Planet::setPosition(const sf::Vector2<double>& pos) { position = pos; }
void Planet::setVelocity(const sf::Vector2<double>& vel) { velocity = vel; }

// Move the planet based on its velocity and the delta time
void Planet::move(double deltaTime) {
    position += velocity * deltaTime; 
}
