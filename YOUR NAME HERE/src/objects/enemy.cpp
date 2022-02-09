#include "enemy.hpp"

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
//---------------------------------------------------------------------------------
