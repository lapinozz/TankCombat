#include "inc/world.hpp"
#include <cmath>

namespace tc {
	/**
	 * \brief Constructor.
	 *
	 * Build the world. Calls helper methods.
	 * @param window The RenderWindow to draw to.
	 * @see load_textures()
	 * @see load_sounds()
	 * @see build_scene
	 */
	World::World(sf::RenderWindow &window) : window(window), world_view(window.getDefaultView()), textures(), sounds(), scene_graph(), scene_layers(), world_bounds(0.f, 0.f, this->world_view.getSize().x, this->world_view.getSize().y), spawn_position(this->world_view.getSize().x / 2.f, this->world_bounds.height - this->world_view.getSize().y / 2.f), player_tank(nullptr), command_queue() {
		this->load_textures();
		this->load_sounds();
		this->build_scene();
		this->world_view.setCenter(this->spawn_position);
	}

	/**
	 * \brief Updates the whole world.
	 *
	 * Proceeds command queue, triggers update on the scene graph.
	 *
	 * @param dt The time passed.
	 */
	void World::update(sf::Time dt) {
		this->player_tank->set_movement(0.f);
		while (!this->command_queue.is_empty()) {
			this->scene_graph.on_command(this->command_queue.pop(), dt);
		}
		this->adapt_player_movement();
		this->scene_graph.update(dt);
		this->adapt_player_position();
		return;
	}

	/**
	 * \brief Draws the whole world.
	 *
	 * Triggers draw on the scene graph.
	 */
	void World::draw() {
		this->window.setView(this->world_view);
		this->window.draw(this->scene_graph);
		return;
	}

	/**
	 * \brief Gets the command queue.
	 *
	 * Makes the command queue available for the other parts needing it.
	 *
	 * @return The command queue.
	 */
	CommandQueue& World::get_command_queue() {
		return this->command_queue;
	}

	/**
	 * \brief Loads the textures needed into the TextureManager.
	 *
	 * Textures are loaded from the media files right into the manager.
	 */
	void World::load_textures() {
		this->textures.load(Textures::Tank, "media/Textures/Tanks/tankGreen_outline.png");
		this->textures.load(Textures::Turret, "media/Textures/Tanks/barrelGreen_outline.png");
		return;
	}

	/**
	 * \brief Loads the sounds needed into the SoundManager.
	 *
	 * Sounds are loaded from the media files right into the manager.
	 */
	void World::load_sounds() {
		this->sounds.load(Sounds::Idle, "media/Sounds/tank-idle.ogg");
		this->sounds.load(Sounds::Moving, "media/Sounds/tank-moving.ogg");
		return;
	}

	/**
	 * \brief Build the scene graph.
	 *
	 * Creates the scene layers and fills them with appropriate nodes.
	 */
	void World::build_scene() {
		for (std::size_t i = 0; i < static_cast<std::size_t>(Layer::LayerCount); ++i) {
			SceneNode::SceneNodePtr layer(new SceneNode());
			this->scene_layers[i] = layer.get();
			this->scene_graph.attach_child(std::move(layer));
		}
		std::unique_ptr<Tank> player_tank(new Tank(this->textures, this->sounds));
		this->player_tank = player_tank.get();
		this->player_tank->setPosition(this->spawn_position);
		this->player_tank->set_movement(0.f);
		this->scene_layers[static_cast<std::size_t>(Layer::Tanks)]->attach_child(std::move(player_tank));
		return;
	}

	/**
	 * \brief Prevents the player to leave the map.
	 *
	 * If player leaves the map, it pushes them back.
	 */
	void World::adapt_player_position() {
		sf::FloatRect view_bounds(this->world_view.getCenter() - this->world_view.getSize() / 2.f, this->world_view.getSize());
		const float border_distance = 30.f;
		sf::Vector2f position = this->player_tank->getPosition();
		position.x = std::max(position.x, view_bounds.left + border_distance);
		position.x = std::min(position.x, view_bounds.left + view_bounds.width - border_distance);
		position.y = std::max(position.y, view_bounds.top + border_distance);
		position.y = std::min(position.y, view_bounds.top + view_bounds.height - border_distance);
		this->player_tank->setPosition(position);
		return;
	}

	/**
	 * \brief Corrects player's speed.
	 *
	 * Not used currently, but may be implemented in the future should need arise.
	 */
	void World::adapt_player_movement() {
		return;
	}
}
