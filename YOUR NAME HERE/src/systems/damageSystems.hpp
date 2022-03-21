#pragma once
#include "../ecs/types.hpp"
#include "../components/components.hpp"

class DamageSystem: public BaseSystem {
private:
	void handleDamage();

	void doDamage(DamageComponent &damageObject, const Group &targetObjects);

public:
	void update() override;
};