#ifndef CATEGORY_HPP
#define CATEGORY_HPP

namespace tc {
	enum class Category {
		None = 0,
		Scene = 1,
		Tank = 1 << 1,
		Turret = 1 << 2,
		Wall = 1 << 3,
	};
}

#endif
