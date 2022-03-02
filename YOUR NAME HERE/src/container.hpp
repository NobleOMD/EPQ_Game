#pragma once
#include <vector>
#include <typeindex>

#include <include/raylib-cpp.hpp>
#include "settings.hpp"
#include "entityComponentSystem.hpp"

// Entity
//---------------------------------------------------------------------------------
inline Group entities;
//---------------------------------------------------------------------------------

//RectangleComponent
//---------------------------------------------------------------------------------
struct PositionComponent {
	ObjectID objectID;
	raylib::Vector2 position;
};

struct SizeComponent {
	ObjectID objectID;
	raylib::Vector2 size;
};
//---------------------------------------------------------------------------------

// TextureComponent
//---------------------------------------------------------------------------------
struct TextureComponent {
	ObjectID objectID;
	raylib::Texture *texture;
	raylib::Rectangle rectangle;
};
//---------------------------------------------------------------------------------

void registerComponents();

struct Actor {
	Actor(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect);
};

inline Group drawnObjects; // Requires Texture and Position components
void drawECS();

