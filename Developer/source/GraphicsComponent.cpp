//GraphicsComponent.cpp

#include <GraphicsComponent.hpp>


//============GraphicsComponent=============
//
GraphicsComponent::~GraphicsComponent() {}

sf::Texture& GraphicsComponent::getTexture() {
	return mTexture;
}

void GraphicsComponent::setTexture(sf::Texture& texture) {
	mTexture = texture;
}
//
//==========================================
