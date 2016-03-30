#include "inc/command.hpp"
#include "inc/category.hpp"
namespace tc {
	Command::Command() : action(), category(static_cast<unsigned int>(Category::None)) {}
}
