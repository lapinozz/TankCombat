#ifndef TANK_HPP
#define TANK_HPP

#include "inc/entity.hpp"
#include "inc/resource_manager.hpp"
#include "inc/enum_class_hash.hpp"

namespace tc {
	class Tank : public Entity {
		public:
			explicit Tank(const TextureManager &textures);
			virtual unsigned int get_category() const override;
		private:
			virtual void draw_current(sf::RenderTarget &target, sf::RenderStates states) const override;
			virtual void update_current(sf::Time dt) override;
			sf::Sprite sprite;
			static const float TANK_SPEED;
			static const float TANK_ROTATION_SPEED;
	};
}
#endif
