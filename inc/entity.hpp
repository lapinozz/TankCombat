#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "inc/scene_node.hpp"

namespace tc {
	/**
	 * \brief Entity represents a movable node of the scene graph.
	 *
	 * Introduces movement and rotation.
	 */
	class Entity : public SceneNode {
		public:
			void set_movement(float movement);
			void set_rotation(float rotation);
			void accelerate(float movement);
			void rotate(float rotation);
			float get_movement() const;
			float get_rotation() const;
		protected:
			float movement;
			float rotation;
		private:
			virtual void update_current(sf::Time dt) override;
	};
}

#endif
