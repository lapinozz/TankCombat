#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <functional>
#include <cassert>
#include <SFML/System.hpp>

namespace tc {
	class SceneNode;

	struct Command {
		public:
			Command();
			std::function<void(SceneNode&, sf::Time)> action;
			unsigned int category;
	};

	template <typename GameObject, typename Function>
	std::function<void(SceneNode&, sf::Time)> derived_action(Function fn) {
		return [=](SceneNode &node, sf::Time dt) -> void {
			assert(dynamic_cast<GameObject*>(&node) != nullptr);
			fn(static_cast<GameObject&>(node), dt);
		};
	}
}
#endif
