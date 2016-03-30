#include "inc/world.hpp"
#include <cmath>

namespace tc {
	World::World(sf::RenderWindow &window) : window(window), world_view(window.getDefaultView()), textures(), sounds(), scene_graph(), scene_layers(), world_bounds(0.f, 0.f, this->world_view.getSize().x, this->world_view.getSize().y), spawn_position(this->world_view.getSize().x / 2.f, this->world_bounds.height - this->world_view.getSize().y / 2.f), player_tank(nullptr), command_queue() {
		this->load_textures();
		this->load_sounds();
		this->build_scene();
		this->world_view.setCenter(this->spawn_position);
	}

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

	void World::draw() {
		this->window.setView(this->world_view);
		this->window.draw(this->scene_graph);
		return;
	}

	CommandQueue& World::get_command_queue() {
		return this->command_queue;
	}

	void World::load_textures() {
		this->textures.load(Textures::Tank, "media/Textures/Tanks/tankGreen_outline.png");
		this->textures.load(Textures::Turret, "media/Textures/Tanks/barrelGreen_outline.png");
		return;
	}

	void World::load_sounds() {
		this->sounds.load(Sounds::Idle, "media/Sounds/tank-idle.ogg");
		this->sounds.load(Sounds::Moving, "media/Sounds/tank-moving.ogg");
		return;
	}

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

	void World::adapt_player_movement() {
		return;
	}
}
