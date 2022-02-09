#include "entity.hpp"

// Entity: combines Textures, Collision and Movement
//---------------------------------------------------------------------------------
Entity::Entity(raylib::Vector2 size, raylib::Vector2 position, raylib::Texture *texture, raylib::Rectangle textureRect)
	:
	ObjectTexture(size, position, texture, textureRect) {
	collisionObjects.push_back(this);
}

void Entity::move(raylib::Vector2 translation) {
	movement(this, translation);
	if (collisionCheck(this, collisionObjects) != nullptr) movement(this, -translation);
}
//---------------------------------------------------------------------------------
