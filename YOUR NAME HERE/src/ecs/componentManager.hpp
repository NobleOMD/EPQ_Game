#pragma once
#include <unordered_map>
#include <memory>
#include <typeindex>

#include "types.hpp"
#include "componentVector.hpp"

struct ComponentManager {
	std::unordered_map<std::type_index, std::shared_ptr<BaseContainer>> componentVectors;

	template<typename Component>
	void newComponent() {
		std::type_index typeName = typeid(Component);
		componentVectors[typeName] = std::make_shared<ComponentVector<Component>>();
	}

	template<typename Component>
	void addComponent(Component component) {
		getComponentVector<Component>()->add(component);
	}

	template<typename Component>
	void removeComponent(ObjectID objectID) {
		getComponentVector<Component>()->remove(objectID);
	}

	template<typename Component>
	Component &getComponent(ObjectID objectID) {
		return getComponentVector<Component>()->get(objectID);
	}

	template<typename Component>
	std::shared_ptr<ComponentVector<Component>> getComponentVector() {
		std::type_index typeName = typeid(Component);
		return std::static_pointer_cast<ComponentVector<Component>>(componentVectors[typeName]);
	}
};