#include <SFML/Graphics.hpp>

const sf::Color Brown(100, 50, 0);

int main() {
	sf::RenderWindow window(sf::VideoMode(640, 480), "Tank Combat");
	sf::Texture tank_texture;
	tank_texture.loadFromFile("media/Textures/Tanks/tankGreen_outline.png");
	sf::Sprite tank;
	tank.setTexture(tank_texture);
	tank.setScale(0.5f, 0.5f);
	tank.setOrigin(tank_texture.getSize().x / 2, tank_texture.getSize().y / 2);
	tank.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				window.close();
			}
			if (e.type == sf::Event::KeyPressed) {
				switch (e.key.code) {
					case sf::Keyboard::Escape:
						window.close();
						break;
					case sf::Keyboard::Up:
					case sf::Keyboard::W:
						tank.move(0, -1);
						break;
					case sf::Keyboard::Down:
					case sf::Keyboard::S:
						tank.move(0, 1);
						break;
					case sf::Keyboard::Left:
					case sf::Keyboard::A:
						tank.move(-1, 0);
						break;
					case sf::Keyboard::Right:
					case sf::Keyboard::D:
						tank.move(1, 0);
						break;
					default:
						break;
				}
			}
		}
		window.clear(Brown);
		window.draw(tank);
		window.display();
	}
	return 0;
}
