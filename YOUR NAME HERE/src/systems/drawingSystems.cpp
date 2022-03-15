#include "drawingSystems.hpp"
#include "../ecs/ECSManager.hpp"
#include "../components/components.hpp"
#include "../settings.hpp"

void DrawTextured::drawTextures() {
	for (ObjectID objectID : group) {
		TextureComponent textureComponent = globalManager.getComponent<TextureComponent>(objectID);
		PositionComponent position = globalManager.getComponent<PositionComponent>(objectID);
		SizeComponent size = globalManager.getComponent<SizeComponent>(objectID);

		// Janky texture offset that is used to align texture with collison box
		raylib::Vector2 textureOffset = (size.size * settings::tileSize) - (raylib::Vector2) textureComponent.rectangle.GetSize();

		textureComponent.texture->Draw(
			textureComponent.rectangle,
			(position.position * settings::tileSize) + raylib::Vector2(textureOffset.x / 2, textureOffset.y) // Move the texture inline with the collision box
		);
	}
}

void DrawDebug::drawDebug() {
	for (ObjectID objectID : group) {
		PositionComponent position = globalManager.getComponent<PositionComponent>(objectID);
		SizeComponent size = globalManager.getComponent<SizeComponent>(objectID);

		raylib::Rectangle rectangle{position.position * settings::tileSize, size.size * settings::tileSize};
		rectangle.DrawLines(BLUE);
	}
}

void AnimatedTextures::tickAnimations() {
	for (ObjectID objectID : group) {
		AnimationInfo &animationInfo = globalManager.getComponent<AnimationInfo>(objectID);
		TextureComponent &textureComponent = globalManager.getComponent<TextureComponent>(objectID);

		// Update the timer
		animationInfo.timeRemaining -= GetFrameTime();
		if (animationInfo.timeRemaining >= 0) continue;
		else animationInfo.timeRemaining = animationInfo.timerLength;

		// If the timer completes a cycle tick through the animation
		animationInfo.frameIndex++;
		if (animationInfo.frameIndex >= animationInfo.frameSequence.size()) animationInfo.frameIndex = 0;

		// Update the texture rectangle according to the current frame
		float animationOffset = textureComponent.rectangle.width * animationInfo.frameSequence[animationInfo.frameIndex];
		textureComponent.rectangle.x = animationInfo.frameZero + animationOffset;
	}
}