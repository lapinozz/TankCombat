#include "inc/wall.hpp"
#include "inc/category.hpp"

namespace tc {
	Wall::Wall(const TextureManager &textures, const sf::Vector2f &position) : sprite(textures.get(Textures::Wall)) {
		this->setPosition(position);
		sf::FloatRect bounds = this->sprite.getLocalBounds();
		this->sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	}

	unsigned int Wall::get_category() const {
		return static_cast<unsigned int>(Category::Wall);
	}
	void Wall::draw_current(sf::RenderTarget &target, sf::RenderStates states) const {
		target.draw(this->sprite, states);
		return;
	}

	sf::FloatRect Wall::get_world_bounds() const {
		return sf::FloatRect(this->get_world_position(), sf::Vector2f(this->sprite.getTexture()->getSize()) * this->sprite.getScale().x);
	}
}
