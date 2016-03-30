#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <unordered_map>
#include <string>
#include <memory>
#include <cassert>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "inc/enum_class_hash.hpp"

namespace tc {

	/**
	 * \brief Texture identifiers.
	 *
	 * Each represents a unique texture.
	 */
	enum class Textures {Tank, Turret};

	enum class Sounds {Idle, Moving};

	/**
	 * \brief Generic manager to hold resources.
	 *
	 * Holds resources in unordered_map using EnumClassHash.
	 */
	template <typename Resource, typename Identifier>
	class ResourceManager {
		public:
			void load(Identifier id, const std::string &filename);
			template <typename Parameter>
			void load(Identifier id, const std::string &filename, const Parameter &second_param);
			Resource& get(Identifier id);
			const Resource& get(Identifier id) const;
		private:
			void insert_resource(Identifier id, std::unique_ptr<Resource> resource);
			std::unordered_map<Identifier, std::unique_ptr<Resource>, EnumClassHash> resource_map;
	};

	typedef ResourceManager<sf::Texture, Textures> TextureManager;
	typedef ResourceManager<sf::SoundBuffer, Sounds> SoundManager;

	/**
	 * \brief General usage load method.
	 *
	 * Loads common resources.
	 *
	 * @param id Appropriate identifier.
	 * @param filename A file to load resource from.
	 */
	template <typename Resource, typename Identifier>
	void ResourceManager<Resource, Identifier>::load(Identifier id, const std::string &filename) {
		std::unique_ptr<Resource> resource(new Resource());
		if (!resource->loadFromFile(filename)) {
			throw std::runtime_error("ResourceManager::load - Failed to load " + filename);
		}
		this->insert_resource(id, std::move(resource));
		return;
	}

	/**
	 * \brief Special usage load method.
	 *
	 * Loads complex resources including shaders.
	 *
	 * @param id Appropriate identifier.
	 * @param filename A file to load resource from.
	 */
	template <typename Resource, typename Identifier>
	template <typename Parameter>
	void ResourceManager<Resource, Identifier>::load(Identifier id, const std::string &filename, const Parameter &second_param) {
		std::unique_ptr<Resource> resource(new Resource());
		if (!resource->loadFromFile(filename, second_param)) {
			throw std::runtime_error("ResourceManager::load - Failed to load " + filename);
		}
		this->insert_resource(id, std::move(resource));
		return;
	}

	/**
	 * \brief General usage get method.
	 *
	 * Returns the resource by it's identifier.
	 *
	 * @param id Appropriate identifier.
	 * @return The resource asked.
	 */
	template <typename Resource, typename Identifier>
	Resource& ResourceManager<Resource, Identifier>::get(Identifier id) {
		auto found = this->resource_map.find(id);
		assert(found != this->resource_map.end());
		return *found->second;
	}

	/**
	 * \brief Constant get method.
	 *
	 * Returns the resource by it's identifier.
	 *
	 * @param id Appropriate identifier.
	 * @return The resource asked.
	 */
	template <typename Resource, typename Identifier>
	const Resource& ResourceManager<Resource, Identifier>::get(Identifier id) const {
		auto found = this->resource_map.find(id);
		assert(found != this->resource_map.end());
		return *found->second;
	}

	/**
	 * \brief Ensures the insertion happens.
	 *
	 * Uses assert.
	 *
	 * @param id Appropriate identifier.
	 * @param resource the unique_ptr to move in.
	 */
	template <typename Resource, typename Identifier>
	void ResourceManager<Resource, Identifier>::insert_resource(Identifier id, std::unique_ptr<Resource> resource) {
		auto inserted = this->resource_map.insert(std::make_pair(id, std::move(resource)));
		assert(inserted.second);
		return;
	}
}

#endif
