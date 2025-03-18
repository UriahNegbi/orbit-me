#include "Game.h"

bool showEditPlanet = false;
bool selectingPosition = false;
sf::Vector2<double> selectedPosition(0.0, 0.0);
ImVec4 selectedColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

void Game::initUi() {
    ImGui::SFML::Init(*window);
}

void Game::simulationSettingsUi() {
    ImGui::Begin("Planet Controls");

    ImGui::Text("Current Planet: %zu", currentPlanetIndex);

    if (ImGui::Button("Toggle Orbit Trail")) {
        orbitTrail = !orbitTrail;
    }

    if (ImGui::Button("Add Planet")) {
        showEditPlanet = !showEditPlanet;
    }

    ImGui::InputFloat("Speed Input", &speed, 0.1f, 1.0f, "%.3f");

    ImGui::InputDouble("TimeStep Input", &simulator.timeStep, 0.000000001, 0.00000001, "%.9f");
    if (simulator.timeStep < 0) {
        simulator.timeStep = simulator.getTimeStepTmp();
    }

    ImGui::End();

    if (showEditPlanet) {
        addPlanetUi();
    }
}

void Game::addPlanetUi() {
    ImGui::Begin("Add Planet", &showEditPlanet);

    ImGui::Text("Planet Settings");
    static float mass = 1.0f;
    static float radius = 10.0f;
    static sf::Vector2<float> velocity(0.0f, 0.0f);  // Velocity input

    ImGui::InputFloat("Mass", &mass);
    ImGui::InputFloat("Radius", &radius);

    // Add input fields for velocity
    ImGui::InputFloat2("Velocity", &velocity.x);  // Velocity in x and y

    // Color Picker using ImGui's built-in color picker
    ImGui::ColorEdit3("Planet Color", (float*)&selectedColor);

    // Position Selection
    if (!selectingPosition) {
        if (ImGui::Button("Select Position")) {
            selectingPosition = true;
        }
    }
    else {
        ImGui::Text("Click to select position");
        ImGui::Text("Selected Position: (%.1f, %.1f)", selectedPosition.x, selectedPosition.y);

        // Get mouse position relative to the window
        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

        // Convert mouse position to world coordinates
        sf::Vector2f worldPos = window->mapPixelToCoords(mousePos, view);

        // Check if the mouse is inside the window boundaries
        if (mousePos.x >= 0 && mousePos.x <= static_cast<int>(window->getSize().x) &&
            mousePos.y >= 0 && mousePos.y <= static_cast<int>(window->getSize().y)) {

            // Confirm the position on mouse click
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                selectedPosition.x = worldPos.x;
                selectedPosition.y = worldPos.y;
                selectingPosition = false;
            }
        }
    }

    if (ImGui::Button("Create")) {
        // Convert ImGui color to SFML color
        sf::Color planetColor = sf::Color(
            static_cast<sf::Uint8>(selectedColor.x * 255),
            static_cast<sf::Uint8>(selectedColor.y * 255),
            static_cast<sf::Uint8>(selectedColor.z * 255)
        );

        // Use the velocity input as the initial velocity for the planet
        addPlanet(Planet(radius, planetColor, selectedPosition, sf::Vector2<double>(velocity.x, velocity.y), mass));
        showEditPlanet = false;
    }

    ImGui::SameLine();

    if (ImGui::Button("Cancel")) {
        showEditPlanet = false;
    }

    ImGui::End();
}


void Game::updateUi() {
    ImGui::SFML::Update(*window, sf::seconds(1.f / 60.f));
    simulationSettingsUi();
}

void Game::renderUi() {
    ImGui::Render();
    ImGui::SFML::Render(*window);
}
