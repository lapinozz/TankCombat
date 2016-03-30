#include "inc/scene_node.hpp"
#include <cassert>
#include <algorithm>
#include "inc/category.hpp"

namespace tc {
	SceneNode::SceneNode() : children(), parent(nullptr) {}

	void SceneNode::attach_child(SceneNodePtr child) {
		child->parent = this;
		this->children.push_back(std::move(child));
		return;
	}

	SceneNode::SceneNodePtr SceneNode::detach_child(const SceneNode &node) {
		auto found = std::find_if(this->children.begin(), this->children.end(), [&](SceneNodePtr &p) -> bool {return p.get() == &node;});
		assert(found != this->children.end());
		SceneNodePtr result = std::move(*found);
		result->parent = nullptr;
		this->children.erase(found);
		return result;
	}

	void SceneNode::update(sf::Time dt) {
		this->update_current(dt);
		this->update_children(dt);
		return;
	}

	sf::Transform SceneNode::get_world_transform() const {
		sf::Transform transform = sf::Transform::Identity;
		for (const SceneNode *node = this; node != nullptr; node = node->parent) {
			transform *= node->getTransform();
		}
		return transform;
	}

	sf::Vector2f SceneNode::get_world_position() const {
		return this->get_world_transform() * sf::Vector2f();
	}

	unsigned int SceneNode::get_category() const {
		return static_cast<unsigned int>(Category::Scene);
	}

	void SceneNode::on_command(const Command &command, sf::Time dt) {
		if (command.category & this->get_category()) {
			command.action(*this, dt);
		}
		for (auto &child : this->children) {
			child->on_command(command, dt);
		}
		return;
	}

	void SceneNode::draw(sf::RenderTarget &target, sf::RenderStates states) const {
		states.transform *= this->getTransform();
		this->draw_current(target, states);
		this->draw_children(target, states);
		return;
	}

	void SceneNode::draw_current(sf::RenderTarget &target, sf::RenderStates states) const {
		return;
	}

	void SceneNode::draw_children(sf::RenderTarget &target, sf::RenderStates states) const {
		for (auto &child : this->children) {
			child->draw(target, states);
		}
		return;
	}

	void SceneNode::update_current(sf::Time dt) {
		return;
	}

	void SceneNode::update_children(sf::Time dt) {
		for (auto &child : this->children) {
			child->update(dt);
		}
		return;
	}
}
