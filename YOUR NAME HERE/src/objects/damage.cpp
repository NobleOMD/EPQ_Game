#include "damage.hpp"

Damage::Damage(raylib::Vector2 size, raylib::Vector2 position, float damage, std::vector<Entity *> &targets)
	:
	ObjectRectangle(size, position),
	damage(damage),
	targets(targets) {
}

void Damage::update() {
	for (Entity *target : damageableEntities) {
		if (CheckCollisionRecs(*target, *this) && target->health > 0) {
			target->health -= damage;
		}
	}
}
