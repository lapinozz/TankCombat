#include "inc/game.hpp"
#include <cmath>

namespace tc {

	/**
	 * \brief The time per frame constant.
	 *
	 * Limits the updates per second, fixes the timestep.
	 */
	const sf::Time Game::TIME_PER_FRAME = sf::seconds(1.f / 60.f);

	/**
	 * \brief Inits the Game object and prepares it to be run.
	 *
	 * Instantiates the world, sets up the statistics.
	 */
	Game::Game() : window(sf::VideoMode(640, 480), "Tank Combat"), world(window), player(), font(), statistics_text(), statistics_update_time(), statistics_num_frames(0) {
		if (!this->font.loadFromFile("media/sansation.ttf")) {
			throw std::runtime_error("Game::Game - Failed to load media/sansation.ttf");
		}
		this->statistics_text.setFont(this->font);
		this->statistics_text.setPosition(5.f, 5.f);
		this->statistics_text.setCharacterSize(10);
	}

	/**
	 * \brief Runs the state.
	 *
	 * Implements fixed timestep.
	 *
	 * @see [Fix your timestep!](http://gafferongames.com/game-physics/fix-your-timestep/)
	 */
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

	/**
	 * \brief Polls events and lets player act upon them.
	 *
	 * Invokes player handle methods.
	 *
	 * @see Player
	 */
	void Game::process_inputs() {
		sf::Event e;
		CommandQueue &commands = this->world.get_command_queue();
		while (this->window.pollEvent(e)) {
			this->player.handle_event(e, commands);
			if (e.type == sf::Event::Closed) {
				this->window.close();
			}
			if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) {
				this->window.close();
			}
		}
		this->player.handle_realtime_input(commands);
		return;
	}

	/**
	 * \brief Updates the model.
	 *
	 * Makes the world update itself.
	 *
	 * @param delta_time The unit of time to forward the model by.
	 * @see World
	 */
	void Game::update(sf::Time delta_time) {
		this->world.update(delta_time);
		return;
	}

	/**
	 * \brief Draws the current state of model.
	 *
	 * Clears the screen, lets the world draw itself, and draws statistics text.
	 */
	void Game::draw() {
		this->world.draw();
		this->window.draw(this->statistics_text);
		this->window.display();
		this->window.clear();
		return;
	}


	/**
	 * \brief Computes statistics.
	 *
	 * Computes frames and update time.
	 *
	 * @param delta_time The unit of time to forward the statistics by.
	 */
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
