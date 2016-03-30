#include "inc/tank.hpp"
#include "inc/category.hpp"
#include <cmath>

namespace tc {
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
		this->setRotation(this->rotation);
		float x = -1 * std::sin(this->getRotation() * M_PI / 180) * this->movement;
		float y = std::cos(this->getRotation() * M_PI / 180) * this->movement;
		this->move(x, y);
		return;
	}
}
