#include "playerInput.hpp"
#include "../ecs/ECSManager.hpp"
#include "systems.hpp"

void PlayerInput::playerInput() {
	Group *player = globalManager.getSystemGroup<PlayerInput>();
	if (player->size() == 0) return;
	ObjectID playerID = *player->begin();

	if (IsKeyPressed(KEY_W)) systems::move(playerID, {0, -1}, systems::collisionObjects);
	if (IsKeyPressed(KEY_A)) systems::move(playerID, {-1, 0}, systems::collisionObjects);
	if (IsKeyPressed(KEY_S)) systems::move(playerID, {0, 1}, systems::collisionObjects);
	if (IsKeyPressed(KEY_D)) systems::move(playerID, {1, 0}, systems::collisionObjects);
}
