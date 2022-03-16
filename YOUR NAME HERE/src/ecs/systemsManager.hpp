#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <vector>

#include "types.hpp"

class SystemManager {
private:
	std::vector<std::shared_ptr<BaseSystem>> systems;
	std::unordered_map<std::type_index, size_t> typeindex_index;
	std::unordered_map<std::type_index, Signature> systemSignatures;

public:
	template <typename System>
	void newSystem(Signature requiredComponents) {
		std::type_index systemTypeName = typeid(System);

		typeindex_index[systemTypeName] = systems.size();
		systems.push_back(std::make_shared<System>());

		systemSignatures[systemTypeName] = requiredComponents;
	}

	template <typename System>
	void addToSystem(ObjectID objectID) {
		std::shared_ptr<System> system = getSystem<System>();
		system->group.insert(objectID);
	}

	template <typename System>
	void removeFromSystem(ObjectID objectID) {
		std::shared_ptr<System> system = getSystem<System>();
		system->group.erase(objectID);
	}

	void removeObject(ObjectID objectID) {
		for (const std::shared_ptr<BaseSystem> &system : systems) {
			system->removeObject(objectID);
		}
	}

	template <typename System>
	std::shared_ptr<System> getSystem() {
		size_t systemIndex = typeindex_index[typeid(System)];
		return std::static_pointer_cast<System>(systems[systemIndex]); // Cast the BaseSystem to the correct templated type
	}

	template <typename System>
	Group *getGroup() {
		return &getSystem<System>()->group;
	}

	template <typename System>
	Signature getSystemSignature() {
		std::type_index systemTypeName = typeid(System);
		return systemSignatures[systemTypeName];
	}

	template <typename System>
	void updateSystem() {
		getSystem<System>()->update();
	}
};
