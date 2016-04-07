#include "inc/wall.hpp"
#include "inc/category.hpp"

namespace tc {
	/**
	 * \brief The constructor.
	 *
	 * Builds up wall on given position.
	 *
	 * @param textures A texture manager.
	 * @param position A position to build this wall.
	 */
	Wall::Wall(const TextureManager &textures, const sf::Vector2f &position) : sprite(textures.get(Textures::Wall)) {
		this->setPosition(position);
		sf::FloatRect bounds = this->sprite.getLocalBounds();
		this->sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	}

	/**
	 * \brief Returns the wall's command category.
	 *
	 * Casted to unsigned int for composite categories.
	 *
	 * @return The command category this wall belongs into.
	 */
	unsigned int Wall::get_category() const {
		return static_cast<unsigned int>(Category::Wall);
	}

	/**
	 * \brief Draws just this wall.
	 *
	 * Is solely responsible for drawing this wall onto the given RenderTarget.
	 *
	 * @param target The RenderTarget to draw to.
	 * @param states The states to apply.
	 */
	void Wall::draw_current(sf::RenderTarget &target, sf::RenderStates states) const {
		target.draw(this->sprite, states);
		return;
	}

	/**
	 * \brief Computes and returns this wall's overall bounds.
	 *
	 * Applies all preceder's transforms via helper function.
	 *
	 * @return The world bounds of this wall.
	 */
	sf::FloatRect Wall::get_world_bounds() const {
		return sf::FloatRect(this->get_world_position(), sf::Vector2f(this->sprite.getTexture()->getSize()) * this->sprite.getScale().x);
	}
}
