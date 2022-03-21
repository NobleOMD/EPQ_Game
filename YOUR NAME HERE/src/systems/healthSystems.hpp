#include "../ecs/types.hpp"

class HealthSystem: public BaseSystem {
private:
	void handleHealth();

public:
	void update() override;
};