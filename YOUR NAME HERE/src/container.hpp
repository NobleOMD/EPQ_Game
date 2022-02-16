#pragma once
#include <vector>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <variant>

#include "settings.hpp"

// Feature
//---------------------------------------------------------------------------------
inline unsigned int createdObjects = 0;

struct Component {
	Component()
		:
		objectID(createdObjects)
	{}

	// Parent object id
	int objectID;
	// Update function that most components should use
	virtual void update() {};
};
//---------------------------------------------------------------------------------

//RectangleComponent
//---------------------------------------------------------------------------------
struct RectangleComponent: public Component {
	RectangleComponent()
		:
		x(0),
		y(0),
		width(0),
		height(0)
	{};

	RectangleComponent(float x, float y, float width, float height)
		:
		x(x),
		y(y),
		width(width),
		height(height)
	{};

	float x, y, width, height;
};
//---------------------------------------------------------------------------------

struct TextureComponent: public Component {
	float *texture;
	RectangleComponent rectangle;
};

// Features
//---------------------------------------------------------------------------------
template <typename TemplateComponent>
inline std::unordered_map<std::type_index, std::unordered_map<unsigned int, TemplateComponent>> allMaps;

template <typename TemplateComponent>
void addComponent(unsigned int objectID, const TemplateComponent component) {
	allMaps<TemplateComponent>[typeid(component)].emplace(objectID, component);
};

template <typename TemplateComponent>
void removeComponent(unsigned int objectID, const TemplateComponent &component) {
	allMaps<TemplateComponent>[typeid(component)].erase(objectID);
};

//inline std::unordered_map<std::type_index, std::unordered_map<unsigned int, Component>> allMaps;
//
//void addComponent(const Component &component) {
//	allMaps[typeid(component)].emplace(component.objectID, component);
//};
//
//void removeComponent(const unsigned int objectID, const Component &component) {
//	allMaps[typeid(component)].erase(objectID);
//};
//---------------------------------------------------------------------------------

// Object
//---------------------------------------------------------------------------------
struct Object {
	Object(std::vector<Component> &requiredComponents) {
		objectID = createdObjects;
		createdObjects++;

		for (Component component : requiredComponents) {
			addComponent(objectID, component);
			Object::requiredComponents.push_back(typeid(component));
		}
	}

	// Object ID used to match objects
	unsigned int objectID;
	std::vector<std::type_index> requiredComponents;
};
//---------------------------------------------------------------------------------
