#pragma once
#include <include/raylib-cpp.hpp>

#include "settings.hpp"
#include "game.hpp"


// GameObject parent class
//---------------------------------------------------------------------------------

class GameObject {
protected:
	// Size / position / grid position
	raylib::Vector2 size; // Size of the object in tiles

	raylib::Vector2 gridPosition; // Position on the tile Grid
	raylib::Vector2 getObjectPosition(); // Function which calculates the object position on screen

	raylib::Rectangle objectRectangle{getObjectPosition(), size * settings::tileSize}; 

	// Colour / texture
	raylib::Color objectColour = BLUE;
	int outlineSize = 1; // Thickness of outline if object outline is drawn

	std::string textureFileName = "textures/default.png"; // Texture filename, this default texture should never appear
	raylib::Vector2 texturePos; // Top left position of texture in texture file above
	raylib::Texture objectTexture{textureFileName};

	// Drawing
	enum drawStates { fill, outline, texture }; // The method of drawing the draw() function will use
	int drawState = drawStates::fill; // The current draw state

	void drawFilled();
	void drawOutline(int thickness);
	void drawTexture(raylib::Texture &texture);

	virtual void update(); // Override this function for subclasses
public:
	GameObject(raylib::Vector2 size, raylib::Vector2 gridPos, raylib::Color colour);
	GameObject(raylib::Vector2 size, raylib::Vector2 gridPos, std::string textureFileName, raylib::Vector2 texturePos = {0, 0});

	// Draw
	void draw(); // Draw with the method defined by drawState
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
	int xp = 0; // Player total xp
	int level = 0; // Player level calculated from xp

	void playerInput(); // Player keyboard input to move / make an action

public:
	using Entity::Entity; // Use the constructors of Entity which in turn uses those of GameObject

	void update(); // Return a value depending on state
};