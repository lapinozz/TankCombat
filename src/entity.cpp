#include "inc/entity.hpp"

namespace tc {
	/**
	 * \brief Sets this entity's movement.
	 *
	 * Inner movement is rewriten by the provided one.
	 *
	 * @param movement The new movement.
	 * @see accelerate(float movement)
	 */
	void Entity::set_movement(float movement) {
		this->movement = movement;
		return;
	}

	/**
	 * \brief Sets this entity's rotation.
	 *
	 * Inner rotation is rewriten by the provided one.
	 *
	 * @param rotation The new rotation.
	 * @see rotate(float rotation)
	 */
	void Entity::set_rotation(float rotation) {
		this->rotation = rotation;
		return;
	}

	/**
	 * \brief Adds to this entity's movement.
	 *
	 * The provided movement is added to the inner one.
	 *
	 * @param movement The movement to add.
	 * @see set_movement(float movement)
	 */
	void Entity::accelerate(float movement) {
		this->movement += movement;
		return;
	}

	/**
	 * \brief Adds to this entity's rotation.
	 *
	 * The provided rotation is added to the inner one.
	 *
	 * @param rotation The rotation to add.
	 * @see set_rotation(float rotation)
	 */
	void Entity::rotate(float rotation) {
		this->rotation += rotation;
		return;
	}

	/**
	 * \brief Gets this entity's movement.
	 *
	 * The inner movement is returned.
	 *
	 * @return This entity's inner movement.
	 */
	float Entity::get_movement() const {
		return this->movement;
	}

	/**
	 * \brief Gets this entity's rotation.
	 *
	 * The inner rotation is returned.
	 *
	 * @return This entity's inner rotation.
	 */
	float Entity::get_rotation() const {
		return this->rotation;
	}

	/**\brief Updates just this entity.
	 *
	 * Is solely responsible for updating the inner state of this entity.
	 *
	 * @param dt The time passed.
	 */
	void Entity::update_current(sf::Time dt) {
		return;
	}
}
