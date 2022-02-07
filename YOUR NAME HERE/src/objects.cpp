#include "objects.hpp"

// ObjectRectangle: base class
//---------------------------------------------------------------------------------
ObjectRectangle::ObjectRectangle(raylib::Vector2 size, raylib::Vector2 position)
	:
	raylib::Rectangle(position * settings::tileSize, size *settings::tileSize),
	size(size),
	position(position) {
	allObjects.push_back(this);
}

void ObjectRectangle::update() {
	x = position.x * settings::tileSize;
	y = position.y * settings::tileSize;

	width = size.x * settings::tileSize;
	height = size.y * settings::tileSize;
}

void ObjectRectangle::draw() {}

void ObjectRectangle::debug() {
	// Draw object outline
	::DrawRectangleLines(static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height), BLUE);
}
//---------------------------------------------------------------------------------


// ObjectTexture: ObjectRectangle drawn with texture
//---------------------------------------------------------------------------------
ObjectTexture::ObjectTexture(raylib::Vector2 size, raylib::Vector2 position, raylib::Texture *texture, raylib::Rectangle textureRect)
	:
	ObjectRectangle(size, position),
	objectTexture(texture),
	textureRect(textureRect) {
}

void ObjectTexture::draw() {
		// Janky texture offset that is used to align texture with collison box
	raylib::Vector2 textureOffset = (raylib::Vector2) this->GetSize() - (raylib::Vector2) textureRect.GetSize();

	objectTexture->Draw(
		textureRect,
		(raylib::Vector2) this->GetPosition() + raylib::Vector2(textureOffset.x / 2, textureOffset.y) // Move the texture inline with the collision box
	);
}
//---------------------------------------------------------------------------------


// Collision: adds collision to ObjectRectangle
//---------------------------------------------------------------------------------

ObjectRectangle *collisionCheck(ObjectRectangle *target, std::vector<ObjectRectangle *> objects) {
	// Check for collision within a list of objects with collison
	for (ObjectRectangle *object : objects) {
		if (target == object) continue; // If the object is ourself continue.

		// If this objects hit box is colliding with another undo the translation
		if (CheckCollisionRecs(*target, *object)) return object;
	}

	return nullptr; // If no collision is found return a nullptr
}

Entity::Entity(raylib::Vector2 size, raylib::Vector2 position, raylib::Texture *texture, raylib::Rectangle textureRect)
	:
	ObjectTexture(size, position, texture, textureRect) {
	collisionObjects.push_back(this);
}
//---------------------------------------------------------------------------------


// Entity: combines Textures with Collision and adds movement
//---------------------------------------------------------------------------------
void movement(ObjectRectangle *target, raylib::Vector2 translation) {
	target->position += translation; // Move by translation vector
	game::clampWithin(settings::gridSize, target->position, target->size); // Clamp within the overall grid
	target->update(); // Update the onscreen position
}
//---------------------------------------------------------------------------------


// Entity: combines Textures, Collision and Movement
//---------------------------------------------------------------------------------
void Entity::move(raylib::Vector2 translation) {
	movement(this, translation);
	if (collisionCheck(this, collisionObjects) != nullptr) movement(this, -translation);
}
//---------------------------------------------------------------------------------


// PlayerCharacter: derived from Entity
//---------------------------------------------------------------------------------
void PlayerCharacter::update() {
	this->ObjectRectangle::update();

	// Player keyboard input to move
	if (IsKeyPressed(KEY_W)) move({0, -1});
	if (IsKeyPressed(KEY_A)) move({-1, 0});
	if (IsKeyPressed(KEY_S)) move({0, 1});
	if (IsKeyPressed(KEY_D)) move({1, 0});
}
//---------------------------------------------------------------------------------


// Enemy: derived from Entity
//---------------------------------------------------------------------------------
Enemy::Enemy(raylib::Vector2 size, raylib::Vector2 position, raylib::Texture *texture, raylib::Rectangle textureRect)
	:
	Entity(size, position, texture, textureRect) {
	enemyObjects.push_back(this);
}

void Enemy::update() {
	// Decrement the timer by frame time
	if (moveTimer >= 0.0f) {
		moveTimer -= GetFrameTime();
		return;
	}

	moveTimer = game::mt19937range(speed - speedRange, speed + speedRange); // Reset the movement timer

	// Move direction vector is faster than switch case
	std::vector<raylib::Vector2> moveDirection{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

	move(moveDirection[game::random() % 4]);
}

// Wall: collision at grid position
//---------------------------------------------------------------------------------
Wall::Wall(raylib::Vector2 gridPos) : ObjectRectangle({1, 1}, gridPos) {
	collisionObjects.push_back(this);
}

