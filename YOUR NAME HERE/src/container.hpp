#pragma once
#include <vector>
#include <unordered_map>
#include <bitset>

#include "settings.hpp"

struct Component {
	// Parent object id
	int objectID;
	// Used to check if object has this component
	std::bitset<settings::MAX_COMPONENTS> componentID;

	// Update function that most components should use
	virtual void update() = 0;
};

struct Object {
	// Object ID used to match objects
	int objectID;
	// Bitmask used to check which components object has
	std::bitset<settings::MAX_COMPONENTS> requiredComponents;
};

template<typename T>
class ComponentContainer;

template<typename T>
struct GlobalContainer {
	// Stores vector of ObjectContainers
	std::vector<ComponentContainer> everything;

	// Update all containers
	void update() {
		for (ComponentContainer components : everything) {
			components.update();
		}
	}
};

template<typename T>
struct ComponentContainer {
	// Stores map object id : component
	std::unordered_map<int, T> components;
	
	// Create new component with object id
	void addComponent(int objectID, T component) {
		components[objectID] = component;
	}
	// Remove component by object id
	void removeComponent(int objectID) {
		components.erase(objectID);
	}
	// Update all objects
	void update() {
		for (T component : components) {
			component.update();
		}
	}
};