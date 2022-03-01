#pragma once
#include <vector>
#include <unordered_map>
#include <cassert>
#include <typeindex>
#include <memory>

#include "settings.hpp"

class BaseComponentVector {}; // Base class that we can cast to the correct type

template <typename Component>
class ComponentVector: public BaseComponentVector {
public:
	std::vector<Component> components;

	void add(Component component) {
		const size_t index = aliveComponents;
		components.push_back(component);
		objectID_index[component.objectID] = aliveComponents;
		aliveComponents++;
	}

	void remove(globals::ObjectID objectID) {
		assert(aliveComponents != 0);

		const size_t index = objectID_index[objectID];
		components[index] = components[aliveComponents - 1];

		aliveComponents--;
	}

	Component &get(globals::ObjectID objectID) {
		return components[objectID_index[objectID]];
	}

private:
	size_t aliveComponents = 0;
	std::unordered_map<uint16_t, size_t> objectID_index;
};

class ComponentManager {
public:
	template<typename Component>
	void newComponent() {
		std::type_index typeName = typeid(Component);
		componentVectors[typeName] = std::make_shared<ComponentVector<Component>>();
	}

	template<typename Component>
	void addComponent(Component component) {
		getComponentVector<Component>()->add(component.objectID, component);
	}

	template<typename Component>
	void removeComponent(globals::ObjectID objectID) {
		getComponentVector<Component>()->remove(objectID);
	}

	template<typename Component>
	Component &getComponent(globals::ObjectID objectID) {
		return getComponentVector<Component>()->get(objectID);
	}

private:
	std::unordered_map<std::type_index, std::shared_ptr<BaseComponentVector>> componentVectors;

	template<typename Component>
	std::shared_ptr<ComponentVector<Component>> getComponentVector() {
		std::type_index typeName = typeid(Component);
		return std::static_pointer_cast<ComponentVector<Component>>(componentVectors[typeName]);
	}
};