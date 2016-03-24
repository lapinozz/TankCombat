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
			void update();
			void draw();
		private:
			sf::RenderWindow window;
			sf::Texture tank_texture;
			sf::Sprite tank;
			sf::Vector2f movement;
	};
}

#endif
