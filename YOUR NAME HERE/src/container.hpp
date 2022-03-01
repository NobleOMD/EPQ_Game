#pragma once
#include <vector>
#include <typeindex>

#include <include/raylib-cpp.hpp>
#include "settings.hpp"
#include "entityComponentSystem.hpp"

// Object
//---------------------------------------------------------------------------------
struct Object {
	Object(std::vector<std::type_index> requiredComponents)
		:
		objectID(globals::createdObjects),
		requiredComponents(requiredComponents) {
		globals::createdObjects++;
		globals::manager.addComponent<Object>(*this);
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
	uint16_t objectID;
};
//---------------------------------------------------------------------------------

//RectangleComponent
//---------------------------------------------------------------------------------
struct RectangleComponent: public Component {
	float x;
	float y;
	float width;
	float height;
};
//---------------------------------------------------------------------------------

// TextureComponent
//---------------------------------------------------------------------------------
struct TextureComponent: public Component {
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
		//addBlob(objectID, RectangleComponent(objectID, position.x, position.y, size.x, size.y));
		//addBlob(objectID, TextureComponent(objectID, texture, textureRect));
	};

	void update() {
		//RectangleComponent &rect = getBlob<RectangleComponent>(objectID);
		//rect.x += 5;
	}
};
//---------------------------------------------------------------------------------
