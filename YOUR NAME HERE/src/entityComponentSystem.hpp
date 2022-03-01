#pragma once
#include <vector>
#include <unordered_map>
#include <cassert>
#include <typeindex>
#include <memory>

using ObjectID = const uint16_t &;
size_t createdObjects = 0;

class BaseComponentVector {}; // Base class that we can cast to the correct type

template <typename Component>
class ComponentVector: public BaseComponentVector {
public:
	std::vector<Component> components;

	void add(ObjectID objectID, Component component) {
		const size_t index = aliveComponents;
		components.push_back(component);

		//index_objectID[aliveComponents] = objectID;
		objectID_index[objectID] = aliveComponents;

		aliveComponents++;
	}

	void remove(ObjectID objectID) {
		assert(aliveComponents != 0);

		const size_t index = objectID_index[objectID];
		components[index] = components[aliveComponents - 1];

		aliveComponents--;
	}

	Component &get(ObjectID objectID) {
		return components[objectID_index[objectID]];
	}

private:
	size_t aliveComponents = 0;

	//std::unordered_map<size_t, uint16_t> index_objectID;
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
	void addComponent(ObjectID entity, Component component) {
		getComponentVector<Component>()->add(entity, component);
	}

	template<typename Component>
	void removeComponent(ObjectID entity) {
		getComponentVector<Component>()->remove(entity);
	}

	template<typename Component>
	Component &getComponent(ObjectID entity) {
		return getComponentVector<Component>()->get(entity);
	}

private:
	std::unordered_map<std::type_index, std::shared_ptr<BaseComponentVector>> componentVectors;

	template<typename Component>
	std::shared_ptr<ComponentVector<Component>> getComponentVector() {
		std::type_index typeName = typeid(Component);
		return std::static_pointer_cast<ComponentVector<Component>>(componentVectors[typeName]);
	}
};