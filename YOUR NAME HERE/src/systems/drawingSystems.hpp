#pragma once
#include "../ecs/types.hpp"

struct DrawTextured: public BaseSystem {
	void update() override {
		drawTextures();
	}

	void drawTextures();
};

struct DrawDebug: public BaseSystem {
	void update() override {
		drawDebug();
	}

	void drawDebug();
};

struct AnimatedTextures: public BaseSystem {
	void update() override {
		tickAnimations();
	}

	void tickAnimations();
};