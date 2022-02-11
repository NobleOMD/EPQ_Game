#include "particle.hpp"
#include "../game.hpp"

void ParticleManager::createParticle(Particle particle) {
	particleVector.push_back(particle);
}

void ParticleManager::updateParticles() {
	const float frameTime = GetFrameTime();
	for (int i = 0; i < particleVector.size(); i++) {
		Particle *particle = &particleVector[i];

		if (particle->frameTime <= 0) {
			particle->onDeath();

			allObjects.erase(allObjects.begin() + particle->id);
			particleVector.erase(particleVector.begin() + i);
		}
		else {
			particle->frameTime -= frameTime;
		}
	}
}

Particle::Particle(ObjectTexture particleTexture, float frameTime)
	:
	ObjectTexture(particleTexture),
	frameTime(frameTime) {
	particleManager.createParticle(*this);
}

void Particle::onDeath() {}

AnimatedTexture::AnimatedTexture(ObjectTexture particleTexture, float frameTime, unsigned int numFrames, unsigned int frameShift)
	:
	Particle(particleTexture, frameTime),
	numFrames(numFrames),
	frameShift(frameShift) {
}

void AnimatedTexture::onDeath() {
	if (numFrames > 1) {
		AnimatedTexture nextFrame = *this;
		nextFrame.textureRect.x += frameShift;
		nextFrame.numFrames--;
		particleManager.createParticle(nextFrame);
	}
}

