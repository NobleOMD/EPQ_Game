#pragma once
#include <assert.h>
#include <vector>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>

#include <include/raylib-cpp.hpp>
#include "settings.hpp"

// Component Storage
//---------------------------------------------------------------------------------
template <typename TemplateComponent>
inline std::unordered_map<std::type_index, std::unordered_map<unsigned int, TemplateComponent>> allComponents;

template <typename TemplateComponent>
void addComponent(const unsigned int &objectID, const TemplateComponent &component) {
	allComponents<TemplateComponent>[typeid(TemplateComponent)].emplace(objectID, component);
};

template <typename TemplateComponent>
void removeComponent(const unsigned int &objectID) {
	allComponents<TemplateComponent>[typeid(TemplateComponent)].erase(objectID);
};

template <typename TemplateComponent>
TemplateComponent getComponent(const unsigned int &objectID) {
	auto &componentMap = allComponents<TemplateComponent>[typeid(TemplateComponent)];
	assert(componentMap.find(objectID) != componentMap.end() && "No component in map with specified object ID.");
	return componentMap.at(objectID);
};

template <typename TemplateComponent>
void replaceComponent(const unsigned int &objectID, const TemplateComponent &replacement) {
	removeComponent<TemplateComponent>(objectID);
	addComponent<TemplateComponent>(objectID, replacement);
};
//---------------------------------------------------------------------------------

// Object
//---------------------------------------------------------------------------------
inline unsigned int createdObjects = 0;

struct Object {
	Object() {
		objectID = createdObjects;
		createdObjects++;
	}

	// Object ID used to match objects
	unsigned int objectID;
	std::vector<std::type_index> requiredComponents;
};
//---------------------------------------------------------------------------------

// Component
//---------------------------------------------------------------------------------
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

// TextureComponent
//---------------------------------------------------------------------------------
struct TextureComponent: public Component {
	TextureComponent(const unsigned int &objectID, float *texture, raylib::Rectangle rectangle)
		:
		Component(objectID),
		texture(texture),
		rectangle(rectangle)
	{};

	float *texture;
	raylib::Rectangle rectangle;
};
//---------------------------------------------------------------------------------
