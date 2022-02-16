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
	Component(const unsigned int &objectID)
		:
		objectID(objectID)
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
		Component(createdObjects),
		x(0),
		y(0),
		width(0),
		height(0)
	{};

	RectangleComponent(const unsigned int &objectID, float x, float y, float width, float height)
		:
		Component(objectID),
		x(x),
		y(y),
		width(width),
		height(height)
	{};

	float x, y, width, height;
};
//---------------------------------------------------------------------------------

struct TextureComponent: public Component {
	TextureComponent() 
		:
		Component(createdObjects),
		texture(nullptr),
		rectangle({createdObjects, 0, 0, 0, 0})
	{}

	TextureComponent(const unsigned int &objectID, float *texture, RectangleComponent rectangle)
		:
		Component(objectID),
		texture(texture),
		rectangle(rectangle)
	{};
	float *texture;
	RectangleComponent rectangle;
};

// Features
//---------------------------------------------------------------------------------
template <typename TemplateComponent>
inline std::unordered_map<std::type_index, std::unordered_map<unsigned int, TemplateComponent>> allMaps;

template <typename TemplateComponent>
void addComponent(const unsigned int &objectID, const TemplateComponent &component) {
	allMaps<TemplateComponent>[typeid(TemplateComponent)].emplace(objectID, component);
};

template <typename TemplateComponent>
void removeComponent(const unsigned int &objectID) {
	allMaps<TemplateComponent>[typeid(TemplateComponent)].erase(objectID);
};

template <typename TemplateComponent>
TemplateComponent getComponent(const unsigned int &objectID) {
	return allMaps<TemplateComponent>[typeid(TemplateComponent)][objectID];
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
