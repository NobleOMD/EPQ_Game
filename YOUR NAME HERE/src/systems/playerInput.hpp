#pragma once
#include "../ecs/types.hpp"

struct PlayerInput: public BaseSystem {
	void update() override {
		playerInput();
	}

	void playerInput();
};