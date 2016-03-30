#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "inc/resource_manager.hpp"
#include "inc/world.hpp"
#include "inc/player.hpp"

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
		private:
			void process_inputs();
			void update(sf::Time delta_time);
			void draw();
			void update_statistics(sf::Time delta_time);
			sf::RenderWindow window;
			static const sf::Time TIME_PER_FRAME;
			TextureManager texture_manager;
			World world;
			Player player;
			sf::Font font;
			sf::Text statistics_text;
			sf::Time statistics_update_time;
			std::size_t statistics_num_frames;
	};
}

#endif
