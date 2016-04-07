#include "inc/world.hpp"
#include <cmath>
#include "inc/wall.hpp"

namespace tc {
	/**
	 * \brief Constructor.
	 *
	 * Build the world. Sets views. Calls helper methods.
	 *
	 * @param window The RenderWindow to draw to.
	 * @see load_textures()
	 * @see load_sounds()
	 * @see build_scene
	 * @see [Tutorial: Using View](https://github.com/SFML/SFML/wiki/Tutorial%3A-Using-View)
	 */
	World::World(sf::RenderWindow &window) : window(window), render_texture(), fixed_view(window.getDefaultView()), camera(sf::Vector2f((2000.f - 640.f) / 2.f, (2000.f - 480.f) / 2.f), sf::Vector2f(640.f, 480.f)), textures(), sounds(), scene_graph(), scene_layers(), world_bounds(0.f, 0.f, this->fixed_view.getSize().x, this->fixed_view.getSize().y), spawn_position(this->fixed_view.getSize().x / 2.f, this->world_bounds.height - this->fixed_view.getSize().y / 2.f), player_tank(nullptr), walls(), command_queue() {
		this->render_texture.create(2000.f, 2000.f);
		this->load_textures();
		this->load_sounds();
		this->build_scene();
		this->fixed_view.setCenter(this->spawn_position);
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
		this->camera.setCenter(this->player_tank->get_world_position());
		return;
	}

	/**
	 * \brief Draws the whole world.
	 *
	 * Triggers draw on the scene graph, builds world render texture, draws using player camera and resets to fixed view.
	 */
	void World::draw() {
		this->render_texture.clear(colour::Brown);
		this->render_texture.draw(this->scene_graph);
		this->render_texture.display();
		sf::Sprite world_sprite(this->render_texture.getTexture());
		this->window.setView(this->camera);
		this->window.draw(world_sprite);
		this->window.setView(this->fixed_view);
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
		this->textures.load(Textures::Wall, "media/Textures/Walls/wall_cube.png");
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
		this->player_tank->setPosition(this->spawn_position + sf::Vector2f((2000.f - 640.f) / 2.f, (2000.f - 480.f) / 2.f));
		this->player_tank->set_movement(0.f);
		this->scene_layers[static_cast<std::size_t>(Layer::Tanks)]->attach_child(std::move(player_tank));
		std::vector<sf::Vector2f> wall_positions = {sf::Vector2f(100, 100), sf::Vector2f(540, 100), sf::Vector2f(100, 380), sf::Vector2f(540, 380)};
		for (auto &wall_position : wall_positions) {
			std::unique_ptr<Wall> wall(new Wall(this->textures, wall_position + sf::Vector2f((2000.f - 640.f) / 2.f, (2000.f - 480.f) / 2.f)));
			this->walls.push_back(wall.get());
			this->scene_layers[static_cast<std::size_t>(Layer::Walls)]->attach_child(std::move(wall));
		}
		return;
	}

	/**
	 * \brief Prevents the player to leave the map and to collide with walls.
	 *
	 * If player leaves the map or enters walls, it pushes them back.
	 */
	void World::adapt_player_position() {
		sf::FloatRect world_bounds(0.f, 0.f, 2000.f, 2000.f);
		const float border_distance = 30.f;
		sf::Vector2f position = this->player_tank->getPosition();
		position.x = std::max(position.x, world_bounds.left + border_distance);
		position.x = std::min(position.x, world_bounds.left + world_bounds.width - border_distance);
		position.y = std::max(position.y, world_bounds.top + border_distance);
		position.y = std::min(position.y, world_bounds.top + world_bounds.height - border_distance);
		this->player_tank->setPosition(position);
		sf::FloatRect tank_position = this->player_tank->get_world_bounds();
		for (auto &wall : this->walls) {
			sf::FloatRect overlap;
			sf::FloatRect wall_position = wall->get_world_bounds();
			if (tank_position.intersects(wall_position, overlap)) {
				auto collision_normal = this->player_tank->getPosition() - wall->getPosition();
                auto manifold = this->get_manifold(overlap, collision_normal);
                this->resolve(manifold);
                break;
			}
		}
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

	/**
	 * \brief Returns the collision manifold.
	 *
	 * Computes the normal vector and overlap of the collision.
	 *
	 * @param overlap The intersection result.
	 * @param collision_normal The difference of positions.
	 * @return The collision manifold, x and y represent the normal vector and z represents the overlap distance.
	 * @see resolve(const sf::Vector3f &manifold)
	 * @see [2D Physics 101 - Pong](http://trederia.blogspot.cz/2016/02/2d-physics-101-pong.html)
	 */
	sf::Vector3f World::get_manifold(const sf::FloatRect &overlap, const sf::Vector2f &collision_normal) {
		sf::Vector3f manifold;
		if (overlap.width < overlap.height) {
			manifold.x = (collision_normal.x < 0) ? -1.f : 1.f;
			manifold.z = overlap.width;
		}
		else {
			manifold.y = (collision_normal.y < 0) ? -1.f : 1.f;
			manifold.z = overlap.height;
		}
		return manifold;
	}

	/**
	 * \brief Resolves the collision.
	 *
	 * Moves the tank back out of the collision.
	 *
	 * @param manifold The collision manifold.
	 * @see get_manifold(const sf::FloatRect &overlap, const sf::Vector2f &collision_normal)
	 * @see [2D Physics 101 - Pong](http://trederia.blogspot.cz/2016/02/2d-physics-101-pong.html)
	 */
	void World::resolve(const sf::Vector3f &manifold) {
		sf::Vector2f normal(manifold.x, manifold.y);
		this->player_tank->move(normal * manifold.z);
		return;
	}
}
