#include "inc/tank.hpp"
#include "inc/category.hpp"
#include <cmath>

namespace tc {
	/**
	 * \brief Returns the Textures value.
	 *
	 * Converts this entity into it's respective Textures value.
	 *
	 * @return The respective Textures value.
	 * @see Textures
	 */
	Textures to_textures() {
		return Textures::Tank;
	}

	/**
	 * \brief Constructor.
	 *
	 * Build the tank object. Sets textures and sounds by querying the appropriate resource managers.
	 *
	 * @param textures A texture manager.
	 * @param sounds A sound manager.
	 * @see TextureManager
	 * @see SoundManager
	 */
	Tank::Tank(const TextureManager &textures, const SoundManager &sounds) : sprite(textures.get(to_textures())), idle(sounds.get(Sounds::Idle)), moving(sounds.get(Sounds::Moving)), was_moving(false) {
		this->idle.setLoop(true);
		this->moving.setLoop(true);
		this->sprite.setScale(0.5f, 0.5f);
		sf::FloatRect bounds = this->sprite.getLocalBounds();
		this->sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	}

	/**
	 * \brief Returns the tank's command category.
	 *
	 * Casted to unsigned int for composite categories.
	 *
	 * @return The command category this tank belongs into.
	 */
	unsigned int Tank::get_category() const {
		return static_cast<unsigned int>(Category::Tank);
	}

	/**
	 * \brief Draws just this tank.
	 *
	 * Is solely responsible for drawing this tank onto the given RenderTarget.
	 *
	 * @param target The RenderTarget to draw to.
	 * @param states The states to apply.
	 */
	void Tank::draw_current(sf::RenderTarget &target, sf::RenderStates states) const {
		target.draw(this->sprite, states);
		return;
	}

	/**
	 * \brief Updates just this tank.
	 *
	 * Is solely responsible for updating the inner state of this tank.
	 *
	 * @param dt The time passed.
	 */
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
