#include "inc/command.hpp"
#include "inc/category.hpp"
namespace tc {
	/**
	 * \brief Constructor.
	 *
	 * Sets the default category to None.
	 */
	Command::Command() : action(), category(static_cast<unsigned int>(Category::None)) {}
}
