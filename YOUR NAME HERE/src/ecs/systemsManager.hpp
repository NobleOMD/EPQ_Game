#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <vector>

#include "types.hpp"

/// Systems manager handles the updating of systems and adding / removing objects from them
class SystemManager {
private:
	std::vector<std::shared_ptr<BaseSystem>> systems;
	std::unordered_map<std::type_index, size_t> typeindex_index;
	std::unordered_map<std::type_index, Signature> systemSignatures;

public:
	/// Create a new system with required components used to check objects have correct components
	template <typename System>
	void registerSystem(Signature requiredComponents) {
		std::type_index systemTypeName = typeid(System);

		typeindex_index[systemTypeName] = systems.size();
		systems.push_back(std::make_shared<System>());

		systemSignatures[systemTypeName] = requiredComponents;
	}

	/// Add an object to specified system
	template <typename System>
	void addToSystem(ObjectID objectID) {
		std::shared_ptr<System> system = getSystem<System>();
		system->group.insert(objectID);
	}

	/// Remove an object from a specified system
	template <typename System>
	void removeFromSystem(ObjectID objectID) {
		std::shared_ptr<System> system = getSystem<System>();
		system->group.erase(objectID);
	}

	/// Remove an object from all systems
	void removeObject(ObjectID objectID);

	/// Get a system
	template <typename System>
	std::shared_ptr<System> getSystem() {
		size_t systemIndex = typeindex_index[typeid(System)];
		return std::static_pointer_cast<System>(systems[systemIndex]); // Cast the BaseSystem to the correct templated type
	}

	/// Get a pointer to a systems group of ObjectID's
	template <typename System>
	Group *getGroup() {
		return &getSystem<System>()->group;
	}

	/// Get a system's signature
	template <typename System>
	Signature getSystemSignature() {
		std::type_index systemTypeName = typeid(System);
		return systemSignatures[systemTypeName];
	}

	/// Update specified system
	template <typename System>
	void updateSystem() {
		getSystem<System>()->update();
	}
};
