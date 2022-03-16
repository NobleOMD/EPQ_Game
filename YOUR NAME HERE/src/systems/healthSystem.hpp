#include "../ecs/types.hpp"

struct HealthSystem: public BaseSystem {
	void update () override {
		handleHealth();
	}

	void handleHealth();
};