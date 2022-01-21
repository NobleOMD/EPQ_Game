#include "entities.hpp"

// Entity parent class
//---------------------------------------------------------------------------------

Entity::Entity(raylib::Vector2 size, raylib::Vector2 gridPos, raylib::Color colour)
	:
	size(size),
	gridPosition(gridPos),
	entityColour(colour)
{
	drawState = drawStates::fill;
}

Entity::Entity(raylib::Vector2 size, raylib::Vector2 gridPos, raylib::Vector2 texturePos)
	:
	size(size),
	gridPosition(gridPos),
	textureRect({texturePos, size * settings::tileSize})
{
	drawState = drawStates::texture;
}


raylib::Vector2 Entity::getEntityPosition()
{
	return gridPosition * settings::tileSize;
}

void Entity::move(raylib::Vector2 translation)
{

	gridPosition += translation; // Move by translation vector

	clampWithin(settings::gridSize, gridPosition, size); // Clamp within the overall grid

	entityRectangle.SetPosition(getEntityPosition()); // Update the onscreen position

}

void Entity::drawFilled()
{
	entityRectangle.Draw(entityColour);
}

void Entity::drawOutline(int thickness)
{
	entityRectangle.DrawLines(entityColour, thickness);
}

void Entity::drawTexture(raylib::Texture &texture)
{
	texture.Draw(textureRect, getEntityPosition());
}




// PlayerCharacter child class
//---------------------------------------------------------------------------------

PlayerCharacter::PlayerCharacter(raylib::Vector2 size, raylib::Vector2 gridPos, raylib::Color colour)
	:
	Entity(size, gridPos, colour)
{
}

PlayerCharacter::PlayerCharacter(raylib::Vector2 size, raylib::Vector2 gridPos, raylib::Vector2 texturePos)
	:
	Entity(size, gridPos, texturePos)
{
}

void PlayerCharacter::playerInput()
{
	if (IsKeyPressed(KEY_W))
	{
		Entity::move({0, -1});
	}
	if (IsKeyPressed(KEY_A))
	{
		Entity::move({-1, 0});
	}
	if (IsKeyPressed(KEY_S))
	{
		Entity::move({0, 1});
	}
	if (IsKeyPressed(KEY_D))
	{
		Entity::move({1, 0});
	}
}

void PlayerCharacter::update()
{
	playerInput();
}

void PlayerCharacter::draw()
{
	switch (drawState)
	{
		case drawStates::fill:
			drawFilled();
			break;
		case drawStates::outline:
			drawOutline(outlineSize);
			break;

		case drawStates::texture:
			drawTexture(entityTextures);
			break;
	}
}