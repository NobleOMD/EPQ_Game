#pragma once
#include <include/raylib-cpp.hpp>

#include "settings.hpp"
#include "game.hpp"

class GameObject;

inline std::vector<GameObject *> gameObjects;

// GameObject base class
//---------------------------------------------------------------------------------

class GameObject {
protected:
	void init();

	// Size / position / grid position

	// Check to see if this object is colliding with any other in given pointer vector
	GameObject *collisionCheck(std::vector<GameObject *> gameObjects);

	raylib::Vector2 size; // Size in tiles

	raylib::Vector2 gridPosition; // Position on tile grid
	raylib::Vector2 getObjectPosition(); // Calculate object position from grid position and tile size


	// Colour / texture
	raylib::Rectangle objectRectangle{getObjectPosition(), size * settings::tileSize}; // Rectangle that represents the size and position of the object

	raylib::Color objectColour = BLUE; // Default colour of debug draw functions

	raylib::Texture *objectTexture = nullptr; // Pointer to the texture the gameobject uses for rendering
	raylib::Rectangle textureRect; // Rectangle that represents the shape and size of the object within the texture above
	const raylib::Vector2 textureOffset = -(raylib::Vector2) textureRect.GetSize() + size * settings::tileSize; // Annoying offset to align texture with collision box

	// Drawing
	enum class drawStates { fill, outline, texture }; // The method of drawing the draw() function will use
	drawStates drawState; // The current draw state

public:
	GameObject(raylib::Vector2 size, raylib::Vector2 gridPos, raylib::Texture *texture, raylib::Rectangle textureRect = {0, 0, 0, 0});

	virtual void update(); // Override this function for subclasses

	// Draw
	void draw(); // Draw with the method defined by drawState

	void drawFilled();
	void drawOutline(int thickness);
	void drawTexture(raylib::Texture &texture);
};

// Entity derived GameObject class
//---------------------------------------------------------------------------------

// An Entity is a GameObject with movement
class Entity: public GameObject {
public:
	using GameObject::GameObject; // Use the constructors of GameObject

	void move(raylib::Vector2 translation); // Move on the grid with a vector translation
};

// PlayerCharacter derived Entity class
//---------------------------------------------------------------------------------

class PlayerCharacter: public Entity {
private:
	int xp = 0; // Entity total xp
	int level = 0; // Entity level calculated from xp

public:
	using Entity::Entity; // Use the constructors of Entity which in turn uses those of GameObject

	// Move the character according to player input
	void update();
};

// Enemy derived Entity class
//---------------------------------------------------------------------------------

class Enemy: public Entity {
private:
	float moveSpeed = 1.2f; 
	float moveTimer = moveSpeed;

public:
	using Entity::Entity; // Use the constructors of Entity which in turn uses those of GameObject

	// Randomly move the Enemy around the screen using timing offsets to make it look more natural
	void update();
};