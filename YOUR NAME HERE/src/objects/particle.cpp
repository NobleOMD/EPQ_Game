#include "particle.hpp"

#include "../game.hpp"

void ParticleManager::createParticle(Particle particle) {
	particleList.push_back(particle);
}

void ParticleManager::updateParticles() {
	const float frameTime = GetFrameTime();
	for (auto particle = particleList.begin(); particle != particleList.end(); particle++) {
		//if (particle->frameTime <= 0) {
		//	particle->onDeath();
		//	particleList.erase(particle);
		//}
		//else {
			particle->frameTime -= frameTime;
			particle->update();
		//}
	}
}

Particle::Particle(ObjectTexture particleTexture, float frameTime)
	:
	ObjectTexture(particleTexture),
	frameTime(frameTime) {
	particleManager.createParticle(*this);
}

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

