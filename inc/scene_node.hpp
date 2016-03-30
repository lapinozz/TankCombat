#ifndef SCENE_NODE_HPP
#define SCENE_NODE_HPP

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

namespace tc {
	class SceneNode : public sf::Drawable, public sf::Transformable, private sf::NonCopyable {
		public:
			typedef std::unique_ptr<SceneNode> SceneNodePtr;
			SceneNode();
			void attach_child(SceneNodePtr child);
			SceneNodePtr detach_child(const SceneNode &node);
			void update(sf::Time dt);
			sf::Transform get_world_transform() const;
			sf::Vector2f get_world_position() const;
			virtual unsigned int get_category() const;
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
