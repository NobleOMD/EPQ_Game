#pragma once
#include "../ecs/types.hpp"

class AIMovement: public BaseSystem {
public:
	void update() override;

private:
	void moveAI();
};