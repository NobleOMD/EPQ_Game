#include "objectTexture.hpp"

// ObjectTexture: ObjectRectangle drawn with texture
//---------------------------------------------------------------------------------
ObjectTexture::ObjectTexture(raylib::Vector2 size, raylib::Vector2 position, raylib::Texture *texture, raylib::Rectangle textureRect)
	:
	ObjectRectangle(size, position),
	objectTexture(texture),
	textureRect(textureRect) {
}

void ObjectTexture::draw() {
	// Janky texture offset that is used to align texture with collison box
	raylib::Vector2 textureOffset = (raylib::Vector2) this->GetSize() - (raylib::Vector2) textureRect.GetSize();

	objectTexture->Draw(
		textureRect,
		(raylib::Vector2) this->GetPosition() + raylib::Vector2(textureOffset.x / 2, textureOffset.y) // Move the texture inline with the collision box
	);
}
//---------------------------------------------------------------------------------
