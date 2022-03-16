#pragma once
#include "../ecs/types.hpp"

class PlayerInput: public BaseSystem {
public:
	void update() override {
		playerInput();
	}

private:
	void playerInput();
};