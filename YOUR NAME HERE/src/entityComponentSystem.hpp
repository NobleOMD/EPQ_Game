#pragma once
#include <vector>
#include <set>
#include <unordered_map>
#include <cassert>
#include <typeindex>
#include <memory>

#include "settings.hpp"

inline uint16_t createdObjects = 0;
using ObjectID = uint16_t;
using Group = std::set<ObjectID>;

class BaseContainer {}; // Base class that we can cast to the correct type

template <typename Component>
class ComponentVector: public BaseContainer {
public:
	std::vector<Component> components;

	void add(Component component) {
		const uint16_t index = aliveComponents;
		components.push_back(component);
		objectID_index[component.objectID] = aliveComponents;
		aliveComponents++;
	}

	void remove(uint16_t objectID) {
		assert(aliveComponents != 0);

		const size_t index = objectID_index[objectID];
		components.erase(components.begin() + index);
		objectID_index.erase(objectID);

		aliveComponents--;
	}

	Component &get(uint16_t objectID) {
		return components[objectID_index[objectID]];
	}

private:
	uint16_t aliveComponents = 0;
	std::unordered_map<uint16_t, size_t> objectID_index;
};

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
	void removeComponent(uint16_t objectID) {
		getComponentVector<Component>()->remove(objectID);
	}

	template<typename Component>
	Component &getComponent(uint16_t objectID) {
		return getComponentVector<Component>()->get(objectID);
	}

	template<typename Component>
	std::shared_ptr<ComponentVector<Component>> getComponentVector() {
		std::type_index typeName = typeid(Component);
		return std::static_pointer_cast<ComponentVector<Component>>(componentVectors[typeName]);
	}
};

inline ComponentManager componentManager;