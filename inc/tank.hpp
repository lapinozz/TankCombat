#ifndef TANK_HPP
#define TANK_HPP

#include "inc/entity.hpp"
#include "inc/resource_manager.hpp"
#include "inc/enum_class_hash.hpp"

namespace tc {
	/**
	 * \brief Our hero, the tank.
	 *
	 * Represents the tank, which is an entity subclass.
	 */
	class Tank : public Entity {
		public:
			explicit Tank(const TextureManager &textures, const SoundManager &sounds);
			virtual unsigned int get_category() const override;
			sf::FloatRect get_world_bounds() const override;
		private:
			virtual void draw_current(sf::RenderTarget &target, sf::RenderStates states) const override;
			virtual void update_current(sf::Time dt) override;
			sf::Sprite sprite;
			sf::Sound idle;
			sf::Sound moving;
			bool was_moving;
	};
}
#endif
