#include "entities.hpp"

// Entity parent class
//---------------------------------------------------------------------------------

Entity::Entity(raylib::Vector2 size, raylib::Vector2 gridPos, raylib::Color colour)
	:
	size(size),
	gridPosition(gridPos),
	entityColour(colour)
{}


raylib::Vector2 Entity::getPosition()
{
	return gridPosition * settings::tileSize;
}

void Entity::move(raylib::Vector2 translation)
{

	gridPosition += translation; // Move by translation vector

	clampWithin(settings::gridSize, gridPosition, size); // Clamp within the overall grid

	rectangle.SetPosition(getPosition()); // Update the onscreen position

}

void Entity::drawFilled()
{
	rectangle.Draw(entityColour);
}

void Entity::drawOutline(int thickness)
{
	rectangle.DrawLines(entityColour, thickness);
}

// PlayerCharacter child class
//---------------------------------------------------------------------------------

PlayerCharacter::PlayerCharacter(raylib::Vector2 size, raylib::Vector2 gridPos, raylib::Color colour)
	:
	Entity(size, gridPos, colour)
{}


void PlayerCharacter::playerInput()
{
	if (IsKeyPressed(KEY_W)) {
		Entity::move({ 0, -1 });
	}
	if (IsKeyPressed(KEY_A)) {
		Entity::move({ -1, 0 });
	}
	if (IsKeyPressed(KEY_S)) {
		Entity::move({ 0, 1 });
	}
	if (IsKeyPressed(KEY_D)) {
		Entity::move({ 1, 0 });
	}
}

void PlayerCharacter::update()
{
	playerInput();

	// State updates
	if (health < 0) { state = -1; } // -1 = 0 HP
}

void PlayerCharacter::draw()
{
	drawOutline(outlineSize);
}