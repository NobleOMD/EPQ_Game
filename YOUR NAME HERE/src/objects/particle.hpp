#pragma once
#include <memory>
#include <list>

#include <include/raylib-cpp.hpp>

#include "objectTexture.hpp"

struct Particle;

// ParticleManager (Complete)
//--------------------------------------------------------------------------------------
class ParticleManager {
public:
	void createParticle(Particle particle);
	void updateParticles();

private:
	std::list<Particle> particleList;
};

inline ParticleManager particleManager;
//--------------------------------------------------------------------------------------

// Particle (Complete)
//--------------------------------------------------------------------------------------
struct Particle: public ObjectTexture {
	Particle(ObjectTexture particleTexture, float frameTime);
	virtual void onDeath() {};

	float frameTime;
};
//--------------------------------------------------------------------------------------

// Animated texture (Complete)
//--------------------------------------------------------------------------------------
struct AnimatedTexture: public Particle {
	AnimatedTexture(ObjectTexture particleTexture, float frameTime, unsigned int numFrames, unsigned int frameShift);
	void onDeath();

	unsigned int numFrames;
	unsigned int frameShift;
};
//--------------------------------------------------------------------------------------
