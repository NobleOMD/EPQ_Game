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

	// Collision between two rectangle objects
	GameObject *collisionCheck(std::vector<GameObject *> gameObjects);

	raylib::Vector2 size; // Size of the object in tiles

	raylib::Vector2 gridPosition; // Position on the tile Grid
	raylib::Vector2 getObjectPosition(); // Function which calculates the object position on screen


	// Colour / texture
	raylib::Color objectColour = BLUE;

	raylib::Texture *objectTexture = nullptr;
	raylib::Rectangle textureRect;
	const raylib::Vector2 textureOffset = -(raylib::Vector2) textureRect.GetSize() + size * settings::tileSize;

	// Drawing
	enum class drawStates { fill, outline, texture }; // The method of drawing the draw() function will use
	drawStates drawState; // The current draw state

public:
	GameObject(raylib::Vector2 size, raylib::Vector2 gridPos, raylib::Texture *texture, raylib::Rectangle textureRect = {0, 0, 0, 0});

	virtual void update(); // Override this function for subclasses

	raylib::Rectangle objectRectangle{getObjectPosition(), size * settings::tileSize};

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
	void update();
};