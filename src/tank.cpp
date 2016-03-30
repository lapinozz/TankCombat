#include "inc/tank.hpp"
#include "inc/category.hpp"
#include <cmath>

namespace tc {
	const float Tank::TANK_SPEED = 100.f;
	const float Tank::TANK_ROTATION_SPEED = 50.f;

	Textures to_textures() {
		return Textures::Tank;
	}

	Tank::Tank(const TextureManager &textures) : sprite(textures.get(to_textures())) {
		this->sprite.setScale(0.5f, 0.5f);
		sf::FloatRect bounds = this->sprite.getLocalBounds();
		this->sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	}

	unsigned int Tank::get_category() const {
		return static_cast<unsigned int>(Category::Tank);
	}

	void Tank::draw_current(sf::RenderTarget &target, sf::RenderStates states) const {
		target.draw(this->sprite, states);
		return;
	}

	void Tank::update_current(sf::Time dt) {
		this->movement -= this->movement;
		this->rotation -= this->rotation;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			this->movement -= 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			this->movement += 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			this->rotation -= 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			this->rotation += 1;
		}
		this->sprite.rotate(this->rotation * this->TANK_ROTATION_SPEED * dt.asSeconds());
		float x = -1 * std::sin(this->sprite.getRotation() * M_PI / 180) * this->movement * this->TANK_SPEED * dt.asSeconds();
		float y = std::cos(this->sprite.getRotation() * M_PI / 180) * this->movement * this->TANK_SPEED * dt.asSeconds();
		this->move(x, y);
		return;
	}
}
