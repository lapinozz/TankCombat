#include "inc/tank.hpp"
#include "inc/category.hpp"
#include <cmath>

namespace tc {
	Textures to_textures() {
		return Textures::Tank;
	}

	Tank::Tank(const TextureManager &textures, const SoundManager &sounds) : sprite(textures.get(to_textures())), idle(sounds.get(Sounds::Idle)), moving(sounds.get(Sounds::Moving)), was_moving(false) {
		this->idle.setLoop(true);
		this->moving.setLoop(true);
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
		if (this->movement) {
			this->idle.pause();
			if (!was_moving) {
				this->moving.play();
			}
			was_moving = true;
		}
		else {
			this->moving.pause();
			if (was_moving) {
				this->idle.play();
			}
			was_moving = false;
		}
		return;
	}
}
