#include "playerInput.hpp"
#include "../ecs/ECSManager.hpp"
#include "collisionSystems.hpp"

void PlayerInput::playerInput() {
	Group *player = globalManager.getSystemGroup<PlayerInput>();
	if (player->size() == 0) return;

	std::shared_ptr<CollisionSystem> collisionSystem = globalManager.getSystem<CollisionSystem>();
	ObjectID playerID = *player->begin();
	Group collisionObjects = *globalManager.getSystemGroup<CollisionObjects>();

	if (IsKeyPressed(KEY_W)) collisionSystem->move(playerID, {0, -1}, collisionObjects);
	if (IsKeyPressed(KEY_A)) collisionSystem->move(playerID, {-1, 0}, collisionObjects);
	if (IsKeyPressed(KEY_S)) collisionSystem->move(playerID, {0, 1}, collisionObjects);
	if (IsKeyPressed(KEY_D)) collisionSystem->move(playerID, {1, 0}, collisionObjects);

	if (IsKeyPressed(KEY_SPACE)) {
		// Create new fireball
	};
}

void PlayerInput::update() {
	playerInput();
}
