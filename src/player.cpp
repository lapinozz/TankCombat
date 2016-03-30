#include "inc/player.hpp"
#include <iostream>
#include "inc/tank.hpp"
#include "inc/category.hpp"

namespace tc {
	struct TankMover {
		public:
			TankMover(float movement) : movement(movement) {}
			void operator()(Tank &tank, sf::Time dt) const {
				tank.accelerate(movement * this->TANK_SPEED * dt.asSeconds());
				return;
			}
			float movement;
			const float TANK_SPEED = 100.f;
	};

	struct TankRotator {
		public:
			TankRotator(float rotation) : rotation(rotation) {}
			void operator()(Tank &tank, sf::Time dt) const {
				tank.rotate(rotation * this->TANK_ROTATION_SPEED * dt.asSeconds());
				return;
			}
			float rotation;
			const float TANK_ROTATION_SPEED = 50.f;
	};

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

	void Player::handle_event(const sf::Event &event, CommandQueue &commands) {
		if (event.type == sf::Event::KeyPressed) {
			auto found = this->key_binding.find(event.key.code);
			if (found != this->key_binding.end() && !this->is_realtime_action(found->second)) {
				commands.push(this->action_binding[found->second]);
			}
		}
		return;
	}

	void Player::handle_realtime_input(CommandQueue &commands) {
		for (auto pair : this->key_binding) {
			if (sf::Keyboard::isKeyPressed(pair.first) && this->is_realtime_action(pair.second)) {
				commands.push(this->action_binding[pair.second]);
			}
		}
		return;
	}

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

	sf::Keyboard::Key Player::get_assigned_key(Action action) const {
		for (auto pair : this->key_binding) {
			if (pair.second == action) {
				return pair.first;
			}
		}
		return sf::Keyboard::Unknown;
	}

	void Player::initialize_actions() {
		this->action_binding[Action::RotateLeft].action = derived_action<Tank>(TankRotator(-1));
		this->action_binding[Action::RotateRight].action = derived_action<Tank>(TankRotator(1));
		this->action_binding[Action::MoveUp].action = derived_action<Tank>(TankMover(-1));
		this->action_binding[Action::MoveDown].action = derived_action<Tank>(TankMover(1));
		return;
	}

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
