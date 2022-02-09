#include "damage.hpp"

Damage::Damage(raylib::Vector2 size, raylib::Vector2 position, float damage)
	:
	ObjectRectangle(size, position),
	damage(damage) {
}

void Damage::update() {
	for (Entity *target : damageableObjects) {
		if (CheckCollisionRecs(*target, *this) && target->health > 0) {
			target->health -= damage;
		}
	}
}
