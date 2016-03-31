#ifndef CATEGORY_HPP
#define CATEGORY_HPP

namespace tc {
	/**
	 * \brief Command categories.
	 *
	 * Lists command categories as bit flags, so they're easily combinable.
	 */
	enum class Category {
		None = 0,
		Scene = 1,
		Tank = 1 << 1,
		Turret = 1 << 2,
		Wall = 1 << 3,
	};
}

#endif
