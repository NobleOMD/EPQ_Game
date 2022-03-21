#pragma once
#include "../ecs/types.hpp"

class DrawTextured: public BaseSystem {
private:
	void drawTextures();

public:
	void update() override;
};

class DrawDebug: public BaseSystem {
private:
	void drawDebug();

public:
	void update() override;
};

class AnimatedTextures: public BaseSystem {
private:
	void tickAnimations();

public:
	void update() override;
};