#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <unordered_map>
#include <SFML/Window.hpp>
#include "inc/command_queue.hpp"
#include "inc/enum_class_hash.hpp"

namespace tc {
	class Player {
		public:
			enum class Action {RotateLeft, RotateRight, MoveUp, MoveDown};
			Player();
			void handle_event(const sf::Event &event, CommandQueue &commands);
			void handle_realtime_input(CommandQueue &commands);
			void assign_key(Action action, sf::Keyboard::Key key);
			sf::Keyboard::Key get_assigned_key(Action action) const;
		private:
			void initialize_actions();
			static bool is_realtime_action(Action action);
			std::unordered_map<sf::Keyboard::Key, Action, EnumClassHash> key_binding;
			std::unordered_map<Action, Command, EnumClassHash> action_binding;
	};
}

#endif
