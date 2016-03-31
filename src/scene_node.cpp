#include "inc/scene_node.hpp"
#include <cassert>
#include <algorithm>
#include "inc/category.hpp"

namespace tc {
	/**
	 * \brief Constructor.
	 *
	 * Quick and clean.
	 */
	SceneNode::SceneNode() : children(), parent(nullptr) {}

	/**
	 * \brief Attaches a child to this node.
	 *
	 * Moves the unique pointer into this node's children vector.
	 *
	 * @param child The child to be attached.
	 */
	void SceneNode::attach_child(SceneNodePtr child) {
		child->parent = this;
		this->children.push_back(std::move(child));
		return;
	}

	/**
	 * \brief Detaches a child of this node and returns it.
	 *
	 * Moves the unique pointer out of the children vector and returns it.
	 *
	 * @param node A reference to node to be detached.
	 * @return The detached node.
	 */
	SceneNode::SceneNodePtr SceneNode::detach_child(const SceneNode &node) {
		auto found = std::find_if(this->children.begin(), this->children.end(), [&](SceneNodePtr &p) -> bool {return p.get() == &node;});
		assert(found != this->children.end());
		SceneNodePtr result = std::move(*found);
		result->parent = nullptr;
		this->children.erase(found);
		return result;
	}

	/**
	 * \brief Updates this node and all of it's children.
	 *
	 * Calls helper methods.
	 *
	 * @param dt The time passed.
	 * @see update_current(sf::Time dt)
	 * @see update_children(sf::Time dt)
	 */
	void SceneNode::update(sf::Time dt) {
		this->update_current(dt);
		this->update_children(dt);
		return;
	}

	/**
	 * \brief Computes and returns this node's overall transform.
	 *
	 * Applies all preceder's transforms as well as this node's one.
	 *
	 * @return The composite transform of this node.
	 */
	sf::Transform SceneNode::get_world_transform() const {
		sf::Transform transform = sf::Transform::Identity;
		for (const SceneNode *node = this; node != nullptr; node = node->parent) {
			transform *= node->getTransform();
		}
		return transform;
	}

	/**
	 * \brief Computes and returns this node's overall position.
	 *
	 * Applies all preceder's transforms via helper function.
	 *
	 * @return The composite position of this node.
	 * @see get_world_transform()
	 */
	sf::Vector2f SceneNode::get_world_position() const {
		return this->get_world_transform() * sf::Vector2f();
	}

	/**
	 * \brief Returns the node's command category.
	 *
	 * Casted to unsigned int for composite categories.
	 *
	 * @return The command category this node belongs into.
	 */
	unsigned int SceneNode::get_category() const {
		return static_cast<unsigned int>(Category::Scene);
	}

	/**
	 * \brief Applies the command to itself and it's children.
	 *
	 * Command is only applied if it's the right category.
	 *
	 * @param command The command to execute.
	 * @param dt The time passed.
	 */
	void SceneNode::on_command(const Command &command, sf::Time dt) {
		if (command.category & this->get_category()) {
			command.action(*this, dt);
		}
		for (auto &child : this->children) {
			child->on_command(command, dt);
		}
		return;
	}

	/**
	 * \brief Draws this node and all of it's children.
	 *
	 * Cals helper methods.
	 *
	 * @param target The RenderTarget to draw to.
	 * @param states The states to apply.
	 * @see draw_current(sf::RenderTarget &target, sf::RenderStates states)
	 * @see draw_children(sf::RenderTarget &target, sf::RenderStates states)
	 */
	void SceneNode::draw(sf::RenderTarget &target, sf::RenderStates states) const {
		states.transform *= this->getTransform();
		this->draw_current(target, states);
		this->draw_children(target, states);
		return;
	}

	/**
	 * \brief Draws just this node.
	 *
	 * Is solely responsible for drawing this node onto the given RenderTarget.
	 *
	 * @param target The RenderTarget to draw to.
	 * @param states The states to apply.
	 * @see draw(sf::RenderTarget &target, sf::RenderStates states)
	 */
	void SceneNode::draw_current(sf::RenderTarget &target, sf::RenderStates states) const {
		return;
	}

	/**
	 * \brief Draws all of this node's children.
	 *
	 * Is solely responsible for drawing all of this node's children onto the given RenderTarget.
	 *
	 * @param target The RenderTarget to draw to.
	 * @param states The states to apply.
	 * @see draw(sf::RenderTarget &target, sf::RenderStates states)
	 */
	void SceneNode::draw_children(sf::RenderTarget &target, sf::RenderStates states) const {
		for (auto &child : this->children) {
			child->draw(target, states);
		}
		return;
	}

	/**
	 * \brief Updates just this node.
	 *
	 * Is solely responsible for updating the inner state of this node.
	 *
	 * @param dt The time passed.
	 * @see update(sf::Time dt)
	 */
	void SceneNode::update_current(sf::Time dt) {
		return;
	}

	/**
	 * \brief Updates all of this node's children.
	 *
	 * Is solely responsible for updating the inner state of all of this node's children.
	 *
	 * @param dt The time passed.
	 * @see update(sf::Time dt)
	 */
	void SceneNode::update_children(sf::Time dt) {
		for (auto &child : this->children) {
			child->update(dt);
		}
		return;
	}
}
