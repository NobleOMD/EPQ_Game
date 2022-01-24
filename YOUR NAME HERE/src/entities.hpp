#pragma once
#include <include/raylib-cpp.hpp>

#include "settings.hpp"
#include "game.hpp"

enum drawStates { fill, outline, texture };

// GameObject parent class
//---------------------------------------------------------------------------------

class GameObject {
protected:
	// Size / position / grid position
	raylib::Vector2 size;

	raylib::Vector2 gridPosition;
	raylib::Vector2 getEntityPosition();

	raylib::Rectangle entityRectangle{getEntityPosition(), size * settings::tileSize};

	// Colour / texture
	raylib::Color entityColour = BLUE;
	int outlineSize = 1;

	raylib::Texture entityTextures;
	raylib::Vector2 texturePos;

	// Drawing
	int drawState = 0;
	void drawFilled();
	void drawOutline(int thickness);
	void drawTexture(raylib::Texture &texture);

public:
	GameObject(raylib::Vector2 size, raylib::Vector2 gridPos, raylib::Color colour, drawStates drawState = drawStates::fill);
	GameObject(raylib::Vector2 size, raylib::Vector2 gridPos, std::string textureFileName, raylib::Vector2 texturePos = {0, 0});

	virtual void update(); // Override this function for subclasses

	// Draw
	void draw();
};

class Entity: public GameObject {
protected:
	float health = 100.0f;

public:
	using GameObject::GameObject; // Use the constructors of GameObject

	// Move
	void move(raylib::Vector2 translation);
};

// PlayerCharacter derived Entity class
//---------------------------------------------------------------------------------

class PlayerCharacter: public Entity {
private:
	int xp = 0;
	int level = 0;

	void playerInput(); // Player keyboard input to move / make an action

public:
	using Entity::Entity;
	//PlayerCharacter(raylib::Vector2 size, raylib::Vector2 gridPos, raylib::Color colour);
	//PlayerCharacter(raylib::Vector2 size, raylib::Vector2 gridPos, raylib::Vector2 texturePos);

	void update(); // Return a value depending on state
};