#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <vector>

#include "types.hpp"

class SystemManager {
private:
	std::unordered_map<std::type_index, std::shared_ptr<BaseSystem>> systems;
	std::unordered_map<std::type_index, Signature> systemSignatures;
	std::unordered_map<ObjectID, std::type_index> objectID_system;

public:
	template<typename System>
	void newSystem(Signature requiredComponents) {
		std::type_index systemTypeName = typeid(System);
		systems[systemTypeName] = std::make_shared<System>();
		systemSignatures[systemTypeName] = requiredComponents;
	}

	template<typename System>
	void addToSystem(ObjectID objectID) {
		BaseSystem &system = getSystem<System>();
		system.group.insert(objectID);

		objectID_system[objectID] = typeid(System);
	}

	void removeObject(ObjectID objectID) {
		for (const auto &pair : systems) {
			const auto &system = pair.second;
			system->removeObject(objectID);
		}
	}

	template<typename System>
	std::shared_ptr<System> &getSystem() {
		std::type_index systemTypeName = typeid(System);
		return std::static_pointer_cast<System>(systems[systemTypeName]); // Cast the BaseSystem to the correct templated type
	}

	template<typename System>
	Signature getSystemSignature() {
		std::type_index systemTypeName = typeid(System);
		return systemSignatures[systemTypeName];
	}
};