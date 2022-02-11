#include "objectRectangle.hpp"

// ObjectRectangle: base class
//---------------------------------------------------------------------------------
ObjectRectangle::ObjectRectangle(raylib::Vector2 size, raylib::Vector2 position)
	:
	raylib::Rectangle(position *settings::tileSize, size *settings::tileSize),
	size(size),
	position(position) {
	id = allObjects.size();
	allObjects.push_back(this);
}

void ObjectRectangle::update() {}

void ObjectRectangle::draw() {}

void ObjectRectangle::debug() {
	// Draw object outline
	::DrawRectangleLines(static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height), BLUE);
}

void ObjectRectangle::updatePosition() {
	x = position.x * settings::tileSize;
	y = position.y * settings::tileSize;

	width = size.x * settings::tileSize;
	height = size.y * settings::tileSize;
}
//---------------------------------------------------------------------------------

// Collision: adds collision to ObjectRectangle
//---------------------------------------------------------------------------------
ObjectRectangle *collisionCheck(ObjectRectangle *testRectangle, std::vector<ObjectRectangle *> objects) {
	// Check for collision within a list of objects with collison
	for (ObjectRectangle *targetRectangle : objects) {
		if (testRectangle == targetRectangle) continue; // If the targetRectangle is ourself continue.

		// If this objects hit box is colliding with another undo the translation
		if (CheckCollisionRecs(*testRectangle, *targetRectangle)) return targetRectangle;
	}

	return nullptr; // If no collision is found return a nullptr
}
//---------------------------------------------------------------------------------


// Movement: adds movement to object rectangles
//---------------------------------------------------------------------------------
void movement(ObjectRectangle *target, raylib::Vector2 translation) {
	target->position += translation; // Move by translation vector
	game::clampWithin(settings::gridSize, target->position, target->size); // Clamp within the overall grid
	target->updatePosition(); // Update the onscreen position
}
//---------------------------------------------------------------------------------