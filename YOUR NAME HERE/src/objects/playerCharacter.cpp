#include "playerCharacter.hpp"

// PlayerCharacter: derived from Entity
//---------------------------------------------------------------------------------
void PlayerCharacter::update() {
	// Player keyboard input to move
	if (IsKeyPressed(KEY_W)) move({0, -1});
	if (IsKeyPressed(KEY_A)) move({-1, 0});
	if (IsKeyPressed(KEY_S)) move({0, 1});
	if (IsKeyPressed(KEY_D)) move({1, 0});
}
//---------------------------------------------------------------------------------

