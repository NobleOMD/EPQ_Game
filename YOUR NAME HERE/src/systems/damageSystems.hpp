#pragma once
#include "../ecs/types.hpp"
#include "../components/components.hpp"

class DamageSystem: public BaseSystem {
public:
	void update() override {
		handleDamage();
	}

private:
	void handleDamage();

	void doDamage(DamageComponent &damageObject, const Group &targetObjects);
};