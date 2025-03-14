#ifndef PLANET_H
#define PLANET_H

#include <SFML/Graphics.hpp>

class Planet {
public:
    Planet(float r, sf::Color col, sf::Vector2<double> pos, sf::Vector2<double> vel, double m);

    // Getters
    double getRadius() const;
    sf::Color getColor() const;
    sf::Vector2<double> getPosition() const;
    sf::Vector2<double> getVelocity() const;
    double getMass() const;

    // Setters
    void setPosition(const sf::Vector2<double>& pos);
    void setVelocity(const sf::Vector2<double>& vel);

    void move(double deltaTime);

private:
    double radius;
    sf::Color color;
    sf::Vector2<double> position;
    sf::Vector2<double> velocity;
    double mass;
};

#endif