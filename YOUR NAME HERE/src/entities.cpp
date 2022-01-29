#include "entities.hpp"

// GameObject base class
//---------------------------------------------------------------------------------

// Construction

GameObject::GameObject(raylib::Vector2 size, raylib::Vector2 gridPos, raylib::Texture *texture, raylib::Rectangle textureRect)
	:
	size(size),
	gridPosition(gridPos),
	objectTexture(texture),
	textureRect(textureRect),
	drawState(drawStates::texture) {
	init();
}

void GameObject::init() {
	gameObjects.push_back(this);
}

// Updates

void GameObject::update() {}

GameObject *GameObject::collisionCheck(std::vector<GameObject *> gameObjects) {
	// Check for collision within the 
	for (GameObject *object : gameObjects) {
		if (this == object) continue; // If the object is ourself continue.

		// If this objects hit box is colliding with another undo the translation
		if (CheckCollisionRecs(this->objectRectangle, object->objectRectangle)) return object;
	}

	return nullptr; // If no collision is found return a nullptr
}

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

void GameObject::drawTexture(raylib::Texture &texture) {
	texture.Draw(
		textureRect,
		getObjectPosition() + raylib::Vector2(textureOffset.x / 2, textureOffset.y) // Move the texture inline with the collision box
	);
}

void GameObject::draw() {
	switch (drawState) {
		case drawStates::fill:
			drawFilled();
			break;
		case drawStates::outline:
			drawOutline(1);
			break;

		case drawStates::texture:
			drawTexture(*objectTexture);
			break;
	}
}

// Entity derived GameObject class
//---------------------------------------------------------------------------------

void Entity::move(raylib::Vector2 translation) {
	gridPosition += translation; // Move by translation vector
	objectRectangle.SetPosition(getObjectPosition()); // Update the onscreen position

	if (collisionCheck(gameObjects) != nullptr) gridPosition -= translation;

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

	moveTimer = game::mt19937range(moveSpeed - 1, moveSpeed); // Reset the movement timer

	// Move direction vector is faster than switch case
	std::vector<raylib::Vector2> moveDirection{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

	move(moveDirection[game::random() % 4]);
}
