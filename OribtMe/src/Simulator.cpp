// Simulator.cpp
#include "Simulator.h"
#include <cmath>
#include <vector>

// Constructor: Takes a list of planets, gravitational constant, and time step
Simulator::Simulator(std::vector<Planet>& planets, double gravitationalConstant, double deltaTime)
    : planets(&planets), G(gravitationalConstant), timeStep(deltaTime) {
}

// Compute gravitational force between all planets and update their velocities and positions
void Simulator::computeGravity() {
    auto& planets_ref = *planets;

    size_t planetCount = planets_ref.size();
    std::vector<sf::Vector2<double>> forces(planetCount, sf::Vector2<double>(0.0, 0.0));

    // Loop through all pairs of planets to compute gravitational interaction
    for (size_t i = 0; i < planetCount; ++i) {
        for (size_t j = i + 1; j < planetCount; ++j) {
            Planet& planetA = planets_ref[i];
            Planet& planetB = planets_ref[j];

            // Calculate the direction vector from planet A to planet B
            sf::Vector2<double> direction = planetB.getPosition() - planetA.getPosition();
            double distance = std::sqrt(direction.x * direction.x + direction.y * direction.y); // Pythagoras theorem

            // Avoid division by zero
            if (distance == 0) continue;

            // Normalize the direction vector
            direction.x /= distance;
            direction.y /= distance;

            // Gravitational force magnitude: F = G * (m1 * m2) / r^2
            double forceMagnitude = G * (planetA.getMass() * planetB.getMass()) / (distance * distance);

            // Gravitational force vector
            sf::Vector2<double> force = direction * forceMagnitude;

            // Accumulate forces for both planets
            forces[i] += force;
            forces[j] -= force; // Equal and opposite force
        }
    }

    // Update velocities and move planets based on accumulated forces
    for (size_t i = 0; i < planetCount; ++i) {
        Planet& planet = planets_ref[i];

        // Calculate velocity change
        sf::Vector2<double> velocityChange = (forces[i] / planet.getMass()) * timeStep;

        // Update velocity and move
        planet.setVelocity(planet.getVelocity() + velocityChange);
        planet.move(timeStep);
    }
}

double Simulator::getTimeStep() {
    return this->timeStep;
}

double Simulator::getTimeStepTmp() {
    return this->tmpTimeStep;
}
