#include "playerInput.hpp"
#include "../game.hpp"
#include "systems.hpp"

void PlayerInput::playerInput() {
	if (game::player == UINT16_MAX) return;

	if (IsKeyPressed(KEY_W)) systems::move(game::player, {0, -1}, systems::collisionObjects);
	if (IsKeyPressed(KEY_A)) systems::move(game::player, {-1, 0}, systems::collisionObjects);
	if (IsKeyPressed(KEY_S)) systems::move(game::player, {0, 1}, systems::collisionObjects);
	if (IsKeyPressed(KEY_D)) systems::move(game::player, {1, 0}, systems::collisionObjects);
}
