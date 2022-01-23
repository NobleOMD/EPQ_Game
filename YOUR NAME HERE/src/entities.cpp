#include "entities.hpp"

// GameObject base class
//---------------------------------------------------------------------------------

GameObject::GameObject(raylib::Vector2 size, raylib::Vector2 gridPos, raylib::Color colour)
	:
	size(size),
	gridPosition(gridPos),
	objectColour(colour)
{
	drawState = drawStates::fill;
}

GameObject::GameObject(raylib::Vector2 size, raylib::Vector2 gridPos, std::string textureFileName, raylib::Vector2 texturePos)
	:
	size(size),
	gridPosition(gridPos),
	textureFileName(textureFileName),
	texturePos(texturePos)
{
	drawState = drawStates::texture;
}

void GameObject::update() {}


raylib::Vector2 GameObject::getObjectPosition() {
	return gridPosition * settings::tileSize;
}


void GameObject::drawFilled() {
	objectRectangle.Draw(objectColour);
}

void GameObject::drawOutline(int thickness) {
	objectRectangle.DrawLines(objectColour, thickness);
}

void GameObject::drawTexture(raylib::Texture &texture) {
	texture.Draw(raylib::Rectangle{texturePos, size * settings::tileSize}, getObjectPosition());
}

void GameObject::draw() {
	switch (drawState) {
		case drawStates::fill:
			drawFilled();
			break;
		case drawStates::outline:
			drawOutline(outlineSize);
			break;

		case drawStates::texture:
			drawTexture(objectTexture);
			break;
	}
}

// Entity derived GameObject class
//---------------------------------------------------------------------------------

void Entity::move(raylib::Vector2 translation) {
	gridPosition += translation; // Move by translation vector
	game::clampWithin(settings::gridSize, gridPosition, size); // Clamp within the overall grid
	objectRectangle.SetPosition(getObjectPosition()); // Update the onscreen position
}


// PlayerCharacter derived Entity class
//---------------------------------------------------------------------------------

void PlayerCharacter::playerInput() {
	if (IsKeyPressed(KEY_W)) { Entity::move({0, -1}); }
	if (IsKeyPressed(KEY_A)) { Entity::move({-1, 0}); }
	if (IsKeyPressed(KEY_S)) { Entity::move({0, 1}); }
	if (IsKeyPressed(KEY_D)) { Entity::move({1, 0}); }
}

void PlayerCharacter::update() {
	playerInput();
}
