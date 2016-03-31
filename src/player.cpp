#include "inc/player.hpp"
#include <iostream>
#include "inc/tank.hpp"
#include "inc/category.hpp"

namespace tc {
	/**
	 * \brief TankMover functor.
	 *
	 * Moves the tank around.
	 */
	struct TankMover {
		public:
			/**
			 * \brief Constructor.
			 *
			 * Sets the movement modifier.
			 *
			 * @param movement The movement modifier.
			 */
			TankMover(float movement) : movement(movement) {}
			/**
			 * \brief The callback.
			 *
			 * Accelerates the tank.
			 *
			 * @param tank The tank to accelerate.
			 * @param dt The time passed.
			 */
			void operator()(Tank &tank, sf::Time dt) const {
				tank.accelerate(movement * this->TANK_SPEED * dt.asSeconds());
				return;
			}
			float movement;
			/**
			 * \brief The basic tank speed constant.
			 *
			 * To be modified by the movement modifier.
			 */
			const float TANK_SPEED = 100.f;
	};

	/**
	 * \brief TankRotator functor.
	 *
	 * Rotates the tank around.
	 */
	struct TankRotator {
		public:
			/**
			 * \brief Constructor.
			 *
			 * Sets the rotation modifier.
			 *
			 * @param rotation The rotation modifier.
			 */
			TankRotator(float rotation) : rotation(rotation) {}
			/**
			 * \brief The callback.
			 *
			 * Rotates the tank.
			 *
			 * @param tank The tank to rotate.
			 * @param dt The time passed.
			 */
			void operator()(Tank &tank, sf::Time dt) const {
				tank.rotate(rotation * this->TANK_ROTATION_SPEED * dt.asSeconds());
				return;
			}
			float rotation;
			/**
			 * \brief The basic tank rotation speed constant.
			 *
			 * To be modified by the rotation modifier.
			 */
			const float TANK_ROTATION_SPEED = 50.f;
	};

	/**
	 * \brief Contructor.
	 *
	 * Build the keybindings. Calls helper method to build the action bindings.
	 *
	 * @see initialize_actions()
	 */
	Player::Player() : key_binding(), action_binding() {
		this->key_binding[sf::Keyboard::Left] = Action::RotateLeft;
		this->key_binding[sf::Keyboard::Right] = Action::RotateRight;
		this->key_binding[sf::Keyboard::Up] = Action::MoveUp;
		this->key_binding[sf::Keyboard::Down] = Action::MoveDown;
		this->initialize_actions();
		for (auto &pair : this->action_binding) {
			pair.second.category = static_cast<unsigned int>(Category::Tank);
		}
	}

	/**
	 * \brief Handles system events.
	 *
	 * Seeks the keybindings for the event keys and queues the command.
	 *
	 * @param event The event received.
	 * @param commands The command queue.
	 */
	void Player::handle_event(const sf::Event &event, CommandQueue &commands) {
		if (event.type == sf::Event::KeyPressed) {
			auto found = this->key_binding.find(event.key.code);
			if (found != this->key_binding.end() && !this->is_realtime_action(found->second)) {
				commands.push(this->action_binding[found->second]);
			}
		}
		return;
	}

	/**
	 * \brief Handles real time inputs.
	 *
	 * Checks if any of the input keys are pressed and queues the command.
	 *
	 * @param commands The command queue.
	 */
	void Player::handle_realtime_input(CommandQueue &commands) {
		for (auto pair : this->key_binding) {
			if (sf::Keyboard::isKeyPressed(pair.first) && this->is_realtime_action(pair.second)) {
				commands.push(this->action_binding[pair.second]);
			}
		}
		return;
	}

	/**
	 * \brief Binds key to the action.
	 *
	 * Seeks any previous keybinding to the given action and removes it.
	 *
	 * @param action The action to be bound.
	 * @param key The key to be bound.
	 */
	void Player::assign_key(Action action, sf::Keyboard::Key key) {
		for (auto iter = this->key_binding.begin(); iter != this->key_binding.end(); ) {
			if (iter->second == action) {
				this->key_binding.erase(iter++);
			}
			else {
				++iter;
			}
		}
		this->key_binding[key] = action;
		return;
	}

	/**
	 * \brief Gets the bound key by action.
	 *
	 * Returns sf::Keybord::Unknown in case of no known keybinding.
	 *
	 * @param action The action to seek keybinding for.
	 * @return The bound key.
	 */
	sf::Keyboard::Key Player::get_assigned_key(Action action) const {
		for (auto pair : this->key_binding) {
			if (pair.second == action) {
				return pair.first;
			}
		}
		return sf::Keyboard::Unknown;
	}

	/**
	 * \brief Initialized action bindings with commands.
	 *
	 * Uses functors and derived actions.
	 *
	 * @see TankMover
	 * @see TankRotator
	 * @see derived_action(Function fn)
	 */
	void Player::initialize_actions() {
		this->action_binding[Action::RotateLeft].action = derived_action<Tank>(TankRotator(-1));
		this->action_binding[Action::RotateRight].action = derived_action<Tank>(TankRotator(1));
		this->action_binding[Action::MoveUp].action = derived_action<Tank>(TankMover(-1));
		this->action_binding[Action::MoveDown].action = derived_action<Tank>(TankMover(1));
		return;
	}

	/**
	 * \brief Determines whether an action is realtime input or event.
	 *
	 * Maps the actions into boolean values determined by their realtimeness.
	 *
	 * @param action The action to be determined.
	 * @return The realtimeness of the given action.
	 */
	bool Player::is_realtime_action(Action action) {
		switch (action) {
			case Action::MoveDown:
			case Action::MoveUp:
			case Action::RotateLeft:
			case Action::RotateRight:
				return true;
			default:
				return false;
		}
	}
}
