#ifndef SCENE_NODE_HPP
#define SCENE_NODE_HPP

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "inc/command.hpp"

namespace tc {
	/**
	 * \brief Represents basic scene graph node.
	 *
	 * Does not do much itself, but is a base class for all other node types in the graph.
	 */
	class SceneNode : public sf::Drawable, public sf::Transformable, private sf::NonCopyable {
		public:
			typedef std::unique_ptr<SceneNode> SceneNodePtr;
			SceneNode();
			void attach_child(SceneNodePtr child);
			SceneNodePtr detach_child(const SceneNode &node);
			void update(sf::Time dt);
			sf::Transform get_world_transform() const;
			sf::Vector2f get_world_position() const;
			virtual sf::FloatRect get_world_bounds() const;
			virtual sf::FloatRect get_local_bounds() const;
			virtual unsigned int get_category() const;
			void on_command(const Command &command, sf::Time dt);
		private:
			virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const final;
			virtual void draw_current(sf::RenderTarget &target, sf::RenderStates states) const;
			void draw_children(sf::RenderTarget &target, sf::RenderStates states) const;
			virtual void update_current(sf::Time dt);
			void update_children(sf::Time dt);
			std::vector<SceneNodePtr> children;
			SceneNode *parent;
	};
}

#endif
