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
template <typename TemplateBlob>
inline std::unordered_map<std::type_index, std::unordered_map<unsigned int, TemplateBlob>> blobContainer;

template <typename TemplateBlob>
void addBlob(const unsigned int &objectID, const TemplateBlob component) {
	blobContainer<TemplateBlob>[typeid(TemplateBlob)].emplace(objectID, component);
};

template <typename TemplateBlob>
void removeBlob(const unsigned int &objectID) {
	blobContainer<TemplateBlob>[typeid(TemplateBlob)].erase(objectID);
};

template <typename TemplateBlob>
TemplateBlob getBlob(const unsigned int &objectID) {
	auto &componentMap = blobContainer<TemplateBlob>[typeid(TemplateBlob)];
	assert(componentMap.find(objectID) != componentMap.end() && "No blob in map with specified object ID.");
	return componentMap.at(objectID);
};

template <typename TemplateBlob>
void replaceBlob(const unsigned int &objectID, const TemplateBlob &replacement) {
	removeBlob<TemplateBlob>(objectID);
	addBlob<TemplateBlob>(objectID, replacement);
};
//---------------------------------------------------------------------------------

// Object
//---------------------------------------------------------------------------------
inline unsigned int createdObjects = 0;

struct Object {
	Object(std::vector<std::type_index> requiredComponents)
		:
		objectID(createdObjects),
		requiredComponents(requiredComponents) {
		createdObjects++;
		addBlob(objectID, this);
	};

	virtual void update() {};

	// Object ID used to match objects
	const unsigned int objectID;
	std::vector<std::type_index> requiredComponents;
};
//---------------------------------------------------------------------------------

// Component
//---------------------------------------------------------------------------------
struct Component {
	Component(const unsigned int &objectID)
		:
		objectID(objectID) {
	}

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
		height(height) {
	};

	float x, y, width, height;
};
//---------------------------------------------------------------------------------

// TextureComponent
//---------------------------------------------------------------------------------
struct TextureComponent: public Component {
	TextureComponent(const unsigned int &objectID, raylib::Texture *texture, raylib::Rectangle rectangle)
		:
		Component(objectID),
		texture(texture),
		rectangle(rectangle) {
	};

	raylib::Texture *texture;
	raylib::Rectangle rectangle;
};
//---------------------------------------------------------------------------------

// EnemyObject
//---------------------------------------------------------------------------------
struct EnemyObject: public Object {
	EnemyObject(raylib::Vector2 size, raylib::Vector2 position, raylib::Texture *texture, raylib::Rectangle textureRect)
		:
		Object({typeid(RectangleComponent), typeid(TextureComponent)}) {
		addBlob(objectID, RectangleComponent(objectID, position.x, position.y, size.x, size.y));
		addBlob(objectID, TextureComponent(objectID, texture, textureRect));
	};

	void update() {
		RectangleComponent rect = getBlob<RectangleComponent>(objectID);
		rect.x += 5;
		replaceBlob<RectangleComponent>(objectID, rect);
	}
};
//---------------------------------------------------------------------------------
