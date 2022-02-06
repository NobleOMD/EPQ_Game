#include "gameObject.hpp"

// GameObject base class
//---------------------------------------------------------------------------------

// Construction

GameObject::GameObject(
	raylib::Vector2 size,
	raylib::Vector2 gridPos,
	raylib::Texture *texture,
	raylib::Rectangle textureRect,
	raylib::Color colour
)
	:
	size(size),
	gridPosition(gridPos),
	objectTexture(texture),
	textureRect(textureRect),
	objectColour(colour) {
	allObjects.push_back(this);
}

// Updates

void GameObject::update() {}

raylib::Vector2 GameObject::getObjectPosition() {
	return gridPosition * settings::tileSize;
}


// Drawing

void GameObject::drawFilled() {
	objectRectangle.Draw(objectColour);
}


void GameObject::drawOutline(int thickness) {
	objectRectangle.DrawLines(objectColour, thickness);
}

void GameObject::drawTexture() {
	// Janky texture offset that is used to align texture with collison box
	raylib::Vector2 textureOffset = (raylib::Vector2) objectRectangle.GetSize() - (raylib::Vector2) textureRect.GetSize();

	objectTexture->Draw(
		textureRect,
		getObjectPosition() + raylib::Vector2(textureOffset.x / 2, textureOffset.y) // Move the texture inline with the collision box
	);
}

void GameObject::draw() {
	drawTexture();
}

// CollisionObject derived GameObject class
//---------------------------------------------------------------------------------

CollisionObject::CollisionObject(raylib::Vector2 size, raylib::Vector2 gridPos, raylib::Texture *texture, raylib::Rectangle textureRect, raylib::Color colour)
	:
	GameObject(size, gridPos, texture, textureRect, colour) {
	collisionObjects.push_back(this);
}

CollisionObject *CollisionObject::collisionCheck(std::vector<CollisionObject *> objects) {
	// Check for collision within the 
	for (CollisionObject *object : objects) {
		if (this == object) continue; // If the object is ourself continue.

		// If this objects hit box is colliding with another undo the translation
		if (CheckCollisionRecs(this->objectRectangle, object->objectRectangle)) return object;
	}

	return nullptr; // If no collision is found return a nullptr
}

// Entity derived GameObject class
//---------------------------------------------------------------------------------

void Entity::move(raylib::Vector2 translation) {
	gridPosition += translation; // Move by translation vector
	objectRectangle.SetPosition(getObjectPosition()); // Update the onscreen position

	if (collisionCheck(collisionObjects) != nullptr) gridPosition -= translation;

	game::clampWithin(settings::gridSize, gridPosition, size); // Clamp within the overall grid
	objectRectangle.SetPosition(getObjectPosition()); // Update the onscreen position
}


// PlayerCharacter derived Entity class
//---------------------------------------------------------------------------------

void PlayerCharacter::update() {
	// Player keyboard input to move
	if (IsKeyPressed(KEY_W)) Entity::move({0, -1});
	if (IsKeyPressed(KEY_A)) Entity::move({-1, 0});
	if (IsKeyPressed(KEY_S)) Entity::move({0, 1});
	if (IsKeyPressed(KEY_D)) Entity::move({1, 0});
}

// Enemy derived Entity class
//---------------------------------------------------------------------------------

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

// Wall derived GameObject class
//---------------------------------------------------------------------------------

Wall::Wall(raylib::Vector2 gridPos)
	:
	CollisionObject({1, 1}, gridPos, nullptr, {0, 0, 0, 0}, {0, 0, 0, 0}) {
	collisionObjects.push_back(this);
}

void Wall::draw() {
	drawFilled();
}

// DamageEntity derived GameObject class
//---------------------------------------------------------------------------------

void DamageEntity::move(raylib::Vector2 translation) {
	gridPosition += translation; // Move by translation vector
	game::clampWithin(settings::gridSize, gridPosition, size); // Clamp within the overall grid
	objectRectangle.SetPosition(getObjectPosition()); // Update the onscreen position
}

void DamageEntity::update() {}