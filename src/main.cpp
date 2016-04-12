#include "inc/game.hpp"
#include "inc/math_utility.hpp"
#include "inc/collision_detection.hpp"

int main() {
	tc::Game g;
	g.run();

	math::normalize(sf::Vector2f(2, 2));
	return 0;
}
