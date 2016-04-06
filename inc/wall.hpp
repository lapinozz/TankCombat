#ifndef WALL_HPP
#define WALL_HPP

#include "inc/scene_node.hpp"
#include <SFML/Graphics.hpp>
#include "inc/resource_manager.hpp"

namespace tc {
	class Wall : public SceneNode {
		public:
			Wall(const TextureManager &textures, const sf::Vector2f &position);
			unsigned int get_category() const override;
			sf::FloatRect get_world_bounds() const override;
		private:
			void draw_current(sf::RenderTarget &target, sf::RenderStates states) const override;
			sf::Sprite sprite;
	};
}

#endif
