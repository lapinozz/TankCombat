#include "inc/game.hpp"

namespace tc {

	const float Game::TANK_SPEED = 100.f;
	const sf::Time Game::TIME_PER_FRAME = sf::seconds(1.f / 60.f);

	Game::Game() : window(sf::VideoMode(640, 480), "Tank Combat"), tank(), turret(), movement(0.f, 0.f), texture_manager(), font(), statistics_text(), statistics_update_time(), statistics_num_frames(0) {
		this->texture_manager.load(Textures::Tank, "media/Textures/Tanks/tankGreen_outline.png");
		this->tank.setTexture(this->texture_manager.get(Textures::Tank));
		this->tank.setScale(0.5f, 0.5f);
		this->tank.setOrigin(this->texture_manager.get(Textures::Tank).getSize().x / 2, this->texture_manager.get(Textures::Tank).getSize().y / 2);
		this->tank.setPosition(this->window.getSize().x / 2, this->window.getSize().y / 2);
		this->texture_manager.load(Textures::Turret, "media/Textures/Tanks/barrelGreen_outline.png");
		this->turret.setTexture(this->texture_manager.get(Textures::Turret));
		this->turret.setScale(0.5f, 0.5f);
		this->turret.setOrigin(this->texture_manager.get(Textures::Turret).getSize().x / 2, this->texture_manager.get(Textures::Turret).getSize().y / 2);
		this->turret.setPosition(this->window.getSize().x / 2, this->window.getSize().y / 2);
		if (!this->font.loadFromFile("media/sansation.ttf")) {
			throw std::runtime_error("Game::Game - Failed to load media/sansation.ttf");
		}
		this->statistics_text.setFont(this->font);
		this->statistics_text.setPosition(5.f, 5.f);
		this->statistics_text.setCharacterSize(10);
	}

	void Game::run() {
		sf::Clock clock;
		sf::Time time_since_last_update = sf::Time::Zero;
		while (this->window.isOpen()) {
			sf::Time elapsed_time = clock.restart();
			time_since_last_update += elapsed_time;
			while (time_since_last_update >= this->TIME_PER_FRAME) {
				time_since_last_update -= this->TIME_PER_FRAME;
				this->process_inputs();
				this->update(this->TIME_PER_FRAME);
			}
			this->update_statistics(elapsed_time);
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

	void Game::update(sf::Time delta_time) {
		this->tank.move(this->movement * this->TANK_SPEED * delta_time.asSeconds());
		this->turret.move(this->movement * this->TANK_SPEED * delta_time.asSeconds());
		return;
	}

	void Game::draw() {
		this->window.clear(colour::Brown);
		this->window.draw(this->tank);
		this->window.draw(this->turret);
		this->window.draw(this->statistics_text);
		this->window.display();
		return;
	}

	void Game::update_statistics(sf::Time delta_time) {
		this->statistics_update_time += delta_time;
		++this->statistics_num_frames;
		if (this->statistics_update_time >= sf::seconds(1.f)) {
			this->statistics_text.setString(L"Frames / Second = " + std::to_wstring(this->statistics_num_frames) + L"\nTime / Update = " + std::to_wstring(this->statistics_update_time.asMicroseconds() / this->statistics_num_frames) + L" µs");
			this->statistics_update_time -= sf::seconds(1.f);
			this->statistics_num_frames = 0;
		}
		return;
	}
}
