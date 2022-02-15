#pragma once
#include <vector>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>

#include "settings.hpp"

// Features
//---------------------------------------------------------------------------------
template <typename TemplateComponent>
inline std::unordered_map<std::type_index, std::unordered_map<unsigned int, TemplateComponent *>> allMaps;

template <typename TemplateComponent>
void addComponent(unsigned int objectID, TemplateComponent *component) {
	allMaps<TemplateComponent>[typeid(component)].emplace(objectID, component);
};

template <typename TemplateComponent>
void removeComponent(unsigned int objectID, TemplateComponent *component) {
	allMaps<TemplateComponent>[typeid(component)].erase(objectID);
};
//---------------------------------------------------------------------------------

// Feature
//---------------------------------------------------------------------------------
struct Component {
	Component(int objectID)
		:
		objectID(objectID)
	{}

	// Parent object id
	int objectID;
	// Update function that most components should use
	virtual void update() {};
};
//---------------------------------------------------------------------------------

// Object
//---------------------------------------------------------------------------------
inline unsigned int createdObjects = 0;

struct Object {
	Object(std::vector<Component> &requiredComponents) 
		:
		objectID(createdObjects)
	{
		for (Component component : requiredComponents) {
			addComponent(objectID, &component);
			Object::requiredComponents.push_back(typeid(component));
		}
	}

	// Object ID used to match objects
	unsigned int objectID;
	std::vector<std::type_index> requiredComponents;
};
//---------------------------------------------------------------------------------

//RectangleComponent
//---------------------------------------------------------------------------------
struct RectangleComponent: public Component {
	RectangleComponent()
		:
		Component(-1),
		x(0),
		y(0),
		width(0),
		height(0)
	{};

	RectangleComponent(float x, float y, float width, float height)
		:
		Component(-1),
		x(x),
		y(y),
		width(width),
		height(height)
	{};

	float x, y, width, height;
};
//---------------------------------------------------------------------------------