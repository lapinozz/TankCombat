#ifndef WORLD_HPP
#define WORLD_HPP

#include <array>
#include <SFML/Graphics.hpp>
#include "inc/tank.hpp"
#include "inc/resource_manager.hpp"
#include "inc/scene_node.hpp"
#include "inc/enum_class_hash.hpp"
#include "inc/command_queue.hpp"

namespace tc {
	class World : private sf::NonCopyable {
		public:
			explicit World(sf::RenderWindow &window);
			void update(sf::Time dt);
			void draw();
			CommandQueue& get_command_queue();
		private:
			enum class Layer {Tanks, LayerCount};
			void load_textures();
			void build_scene();
			void adapt_player_position();
			void adapt_player_movement();
			sf::RenderWindow &window;
			sf::View world_view;
			TextureManager textures;
			SceneNode scene_graph;
			std::array<SceneNode*, static_cast<std::size_t>(Layer::LayerCount)> scene_layers;
			sf::FloatRect world_bounds;
			sf::Vector2f spawn_position;
			Tank *player_tank;
			CommandQueue command_queue;
	};
}

#endif
