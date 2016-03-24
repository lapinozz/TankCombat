#ifndef ENUM_CLASS_HASH_HPP
#define ENUM_CLASS_HASH_HPP

namespace tc {
	struct EnumClassHash {
		template <typename Identifier>
		std::size_t operator()(Identifier id) const {
			return static_cast<std::size_t>(id);
		}
	};
}

#endif
