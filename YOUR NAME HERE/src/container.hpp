#pragma once
#include <unordered_map>
#include <typeinfo>
#include <typeindex>
#include <memory>
#include <assert.h>
#include <vector>

#include <include/raylib-cpp.hpp>
#include "settings.hpp"

// Component Storage
//---------------------------------------------------------------------------------
//#include <array>
//
//constexpr size_t maxComponents = 1024;
//size_t createdObjects = 0;
//
//struct Component {
//	uint16_t objectID;
//};
//
//struct Position: public Component {
//	uint16_t x;
//	uint16_t y;
//};
//
//class ComponentManager {
//public:
//	std::array<Component, maxComponents> components;
//
//	void add(Component component) {
//		components[aliveComponents] = component;
//
//		index_objectID[aliveComponents] = component.objectID;
//		objectID_index[component.objectID] = aliveComponents;
//
//		aliveComponents++;
//	}
//
//	void remove(const uint16_t &objectID) {
//		assert(aliveComponents != 0);
//
//		const size_t index = objectID_index[objectID];
//		components[index] = components[aliveComponents - 1];
//
//		aliveComponents--;
//	}
//
//	Component &get(const uint16_t &objectID) {
//		return components[objectID_index[objectID]];
//	}
//
//protected:
//	size_t aliveComponents = 0;
//
//	std::unordered_map<size_t, uint16_t> index_objectID;
//	std::unordered_map<uint16_t, size_t> objectID_index;
//};

template <typename TemplateBlob>
inline std::unordered_map<std::type_index, std::unordered_map<unsigned int, TemplateBlob>> blobContainer;

template <typename TemplateBlob>
TemplateBlob &getBlob(const unsigned int &objectID) {
	auto &componentMap = blobContainer<TemplateBlob>[typeid(TemplateBlob)];
	assert(componentMap.find(objectID) != componentMap.end() && "No blob in map with specified object ID.");
	return componentMap.at(objectID);
};

template <typename TemplateBlob>
void addBlob(const unsigned int &objectID, const TemplateBlob &component) {
	blobContainer<TemplateBlob>[typeid(TemplateBlob)].emplace(objectID, component);
};

template <typename TemplateBlob>
void removeBlob(const unsigned int &objectID) {
	blobContainer<TemplateBlob>[typeid(TemplateBlob)].erase(objectID);
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
		addBlob(objectID, std::make_unique<Object>(*this));		
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
	}
};
//---------------------------------------------------------------------------------
