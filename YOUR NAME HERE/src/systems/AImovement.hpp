#pragma once
#include "../ecs/types.hpp"

class AIMovement: public BaseSystem {
public:
	void update() override {
		moveAI();
	}

	void moveAI();
private:
};