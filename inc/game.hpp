#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

namespace tc {
	namespace colour {
		const sf::Color Brown(100, 50, 0);
	}
	class Game {
		public:
			Game();
			void run();
			void process_inputs();
			void update(sf::Time delta_time);
			void draw();
		private:
			sf::RenderWindow window;
			sf::Texture tank_texture;
			sf::Sprite tank;
			sf::Vector2f movement;
			static const sf::Time TIME_PER_FRAME;
			static const float TANK_SPEED;
	};
}

#endif
