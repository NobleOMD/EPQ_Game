#pragma once
#include "../ecs/types.hpp"

class PlayerInput: public BaseSystem {
private:
	void playerInput();

public:
	void update() override;
};