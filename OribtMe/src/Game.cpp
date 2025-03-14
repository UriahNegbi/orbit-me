#include "Game.h"
#include <iostream>

void Game::initVariables()
{
    this->window = nullptr;
    this->cameraMode = Free;
    this->currentPlanetIndex = 0;
    this->speed = 5.f;
    this->lockKeyPressed = false;
    this->leftKeyPressed = false;
    this->rightKeyPressed = false;
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
    this->videoMode.height = 600;
    this->videoMode.width = 1000;
    this->window = new sf::RenderWindow(this->videoMode, "Gravity Simulator");
    this->window->setVerticalSyncEnabled(true);
}

void Game::initView()
{
    this->view.setSize(2000.f, 1000.f);
    this->view.setCenter(500.f, 300.f);
}

Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initRenderShapes();
    this->initView();
}

Game::~Game()
{
    delete this->window;
}

const bool Game::running() const
{
    return this->window->isOpen();
}

void Game::pollEvents()
{
	while (window->pollEvent(ev)) {
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
				if (currentPlanetIndex < this->renderObjects.size() - 1) {
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
        renderObjects[i].setPosition((sf::Vector2f)this->objects[i].getPosition());

    }
}

void Game::updateCamera()
{
    if (cameraMode == Lock) {
        view.setCenter(this->renderObjects.at(this->currentPlanetIndex).getPosition());
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
}



void Game::updateControls()
{
    if (this->cameraMode == Free) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            view.move(0.f, -this->speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            view.move(0.f, this->speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            view.move(this->speed, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
           view.move(-this->speed, 0.f);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        view.zoom(0.9f); // Zoom in
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        view.zoom(1.1f); // Zoom out
    }
}


void Game::update()
{
    pollEvents();
    simulator.computeGravity();
    updateControls();
    updateCamera();
    updatePlanet();
}

void Game::renderPlanets()
{
    for (const sf::CircleShape& renderObject : renderObjects) {
        window->draw(renderObject);
    }
}

void Game::render()
{
    window->clear();
    window->setView(view);
    renderPlanets();
    window->display();
}

void Game::setSpeed(float speed)
{
    this->speed = speed;
}

float Game::getSpeed() const
{
    return speed;
}

