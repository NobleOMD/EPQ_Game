#include "../ecs/types.hpp"

class HealthSystem: public BaseSystem {
public:
	void update () override {
		handleHealth();
	}

private:
	void handleHealth();
};