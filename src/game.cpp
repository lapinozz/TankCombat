#include "inc/game.hpp"

namespace tc {
	Game::Game() : window(sf::VideoMode(640, 480), "Tank Combat"), tank_texture(), tank(), movement(0.f, 0.f) {
		this->tank_texture.loadFromFile("media/Textures/Tanks/tankGreen_outline.png");
		this->tank.setTexture(this->tank_texture);
		this->tank.setScale(0.5f, 0.5f);
		this->tank.setOrigin(this->tank_texture.getSize().x / 2, this->tank_texture.getSize().y / 2);
		this->tank.setPosition(this->window.getSize().x / 2, this->window.getSize().y / 2);
	}

	void Game::run() {
		while (this->window.isOpen()) {
			this->process_inputs();
			this->update();
			this->draw();
		}
		return;
	}

	void Game::process_inputs() {
		sf::Event e;
		while (this->window.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				this->window.close();
			}
			if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) {
				this->window.close();
			}
		}
		this->movement -= this->movement;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			this->movement.y -= 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			this->movement.y += 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			this->movement.x -= 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			this->movement.x += 1;
		}
		return;
	}

	void Game::update() {
		this->tank.move(this->movement);
		return;
	}

	void Game::draw() {
		this->window.clear(colour::Brown);
		this->window.draw(this->tank);
		this->window.display();
		return;
	}
}
