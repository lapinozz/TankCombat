#include "inc/entity.hpp"

namespace tc {
	void Entity::set_movement(float movement) {
		this->movement = movement;
		return;
	}

	void Entity::set_rotation(float rotation) {
		this->rotation = rotation;
		return;
	}

	void Entity::accelerate(float movement) {
		this->movement += movement;
		return;
	}

	void Entity::rotate(float rotation) {
		this->rotation += rotation;
		return;
	}

	float Entity::get_movement() const {
		return this->movement;
	}

	float Entity::get_rotation() const {
		return this->rotation;
	}

	void Entity::update_current(sf::Time dt) {
		return;
	}
}
