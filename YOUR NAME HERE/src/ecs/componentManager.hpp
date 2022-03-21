#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>

#include "types.hpp"
#include "componentVector.hpp"

/// ComponentManager stores and handles ComponentVectors of different types
class ComponentManager {
protected:
	std::unordered_map<std::type_index, std::shared_ptr<BaseContainer>> componentVectors; // Map of vector type to pointer to vector

public:
	/// Register a new component by creating a new ComponentVector and adding it to the map
	template<typename Component>
	void newComponentVector() {
		std::type_index componentTypeName = typeid(Component);
		componentVectors[componentTypeName] = std::make_shared<ComponentVector<Component>>();
	}

	/// Add a component to the component vector
	template<typename Component>
	void addComponent(Component component) {
		getComponentVector<Component>()->add(component);
	}

	/// Remove a component by objectID
	template<typename Component>
	void removeComponent(ObjectID objectID) {
		getComponentVector<Component>()->remove(objectID);
	}

	/// Iterate over all the component vectors in the map and call their remove object function
	void removeObject(ObjectID objectID);

	/// Get a component by objectID
	template<typename Component>
	Component &getComponent(ObjectID objectID) {
		return getComponentVector<Component>()->get(objectID);
	}

	/// Get the component vector of template type
	template<typename Component>
	std::shared_ptr<ComponentVector<Component>> getComponentVector() {
		std::type_index componentTypeName = typeid(Component);
		return std::static_pointer_cast<ComponentVector<Component>>(componentVectors[componentTypeName]); // Cast the BaseContainer to the correct templated type
	}
};