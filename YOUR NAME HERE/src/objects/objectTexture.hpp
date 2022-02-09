#pragma once
#include <include/raylib-cpp.hpp>
#include "../settings.hpp"

#include "objectRectangle.hpp"

// ObjectTexture: ObjectRectangle drawn with texture (Complete)
//---------------------------------------------------------------------------------
class ObjectTexture: public ObjectRectangle {
public:
	ObjectTexture(raylib::Vector2 size, raylib::Vector2 position, raylib::Texture *texture, raylib::Rectangle textureRect);
	void draw();

protected:
	// Colour / texture
	raylib::Texture *objectTexture; // Pointer to the texture the gameobject uses for rendering
	raylib::Rectangle textureRect; // Rectangle that represents the shape and size of the object within the texture above
};
//---------------------------------------------------------------------------------
