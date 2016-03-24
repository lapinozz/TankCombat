#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "inc/resource_manager.hpp"

namespace tc {
	namespace colour {
		const sf::Color Brown(100, 50, 0);
	}
	/**
	 * \brief The main game object.
	 *
	 * Runs the whole game.
	 */
	class Game {
		public:
			Game();
			void run();
			void process_inputs();
			void update(sf::Time delta_time);
			void draw();
		private:
			void update_statistics(sf::Time delta_time);
			sf::RenderWindow window;
			sf::Sprite tank;
			sf::Sprite turret;
			float movement;
			float rotation;
			static const sf::Time TIME_PER_FRAME;
			static const float TANK_SPEED;
			static const float TANK_ROTATION_SPEED;
			TextureManager texture_manager;
			sf::Font font;
			sf::Text statistics_text;
			sf::Time statistics_update_time;
			std::size_t statistics_num_frames;
	};
}

#endif
