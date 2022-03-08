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

public:
	template<typename TemplateSystem>
	void newSystem(Signature requiredComponents) {
		std::type_index systemTypeName = typeid(TemplateSystem);
		systems[systemTypeName] = std::make_shared<TemplateSystem>();
		systemSignatures[systemTypeName] = requiredComponents;
	}

	template<typename TemplateSystem>
	void addToSystem(ObjectID objectID) {
		BaseSystem system = getSystem<TemplateSystem>();
		system.group.insert(objectID);
	}

	template<typename TemplateSystem>
	std::shared_ptr<TemplateSystem> getSystem() {
		std::type_index systemTypeName = typeid(TemplateSystem);
		return std::static_pointer_cast<TemplateSystem>(systems[systemTypeName]); // Cast the BaseSystem to the correct templated type
	}

	template<typename TemplateSystem>
	Signature getSystemSignature() {
		std::type_index systemTypeName = typeid(TemplateSystem);
		return systemSignatures[systemTypeName];
	}
};