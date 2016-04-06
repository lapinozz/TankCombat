#ifndef WORLD_HPP
#define WORLD_HPP

#include <array>
#include "inc/tank.hpp"
#include "inc/resource_manager.hpp"
#include "inc/scene_node.hpp"
#include "inc/enum_class_hash.hpp"
#include "inc/command_queue.hpp"
#include "inc/wall.hpp"

namespace tc {
	namespace colour {
		const sf::Color Brown(100, 50, 0);
	}
	/**
	 * \brief Represents the scene.
	 *
	 * Contains scene graph, command queue, resource managers and other stuff.
	 */
	class World : private sf::NonCopyable {
		public:
			explicit World(sf::RenderWindow &window);
			void update(sf::Time dt);
			void draw();
			CommandQueue& get_command_queue();
		private:
			enum class Layer {Tanks, Walls, LayerCount};
			void load_textures();
			void load_sounds();
			void build_scene();
			void adapt_player_position();
			void adapt_player_movement();
			sf::Vector3f get_manifold(const sf::FloatRect &overlap, const sf::Vector2f &collision_normal);
			void resolve(const sf::Vector3f &manifold);
			sf::RenderWindow &window;
			sf::RenderTexture render_texture;
			sf::View world_view;
			sf::View camera;
			TextureManager textures;
			SoundManager sounds;
			SceneNode scene_graph;
			std::array<SceneNode*, static_cast<std::size_t>(Layer::LayerCount)> scene_layers;
			sf::FloatRect world_bounds;
			sf::Vector2f spawn_position;
			Tank *player_tank;
			std::vector<Wall*> walls;
			CommandQueue command_queue;
	};
}

#endif
