#ifndef ENUM_CLASS_HASH_HPP
#define ENUM_CLASS_HASH_HPP

namespace tc {
	/**
	 * \brief Allows enums and enum classes to be hashed.
	 *
	 * Useful for using them as key in unordered_maps and similar containers.
	 *
	 * @param id The enum (class) member.
	 * @return The internal size_t value.
	 */
	struct EnumClassHash {
		template <typename Identifier>
		std::size_t operator()(Identifier id) const {
			return static_cast<std::size_t>(id);
		}
	};
}

#endif
