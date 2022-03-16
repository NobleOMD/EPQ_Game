#pragma once
#include "../ecs/types.hpp"

class DrawTextured: public BaseSystem {
public:
	void update() override {
		drawTextures();
	}

private:
	void drawTextures();
};

class DrawDebug: public BaseSystem {
public:
	void update() override {
		drawDebug();
	}
private:
	void drawDebug();
};

class AnimatedTextures: public BaseSystem {
public:
	void update() override {
		tickAnimations();
	}
private:
	void tickAnimations();
};