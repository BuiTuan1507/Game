#include "Coin.h"


Coin::Coin(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime)
	: SpriteAnimation(model, shader, texture,numFrames,frameTime)
{
	int activeCoin = 1;
}
Coin::~Coin()
{
}
void Coin::setActive(int activeCoin) {
	this->activeCoin = activeCoin;
}
int Coin::getActive() {
	return activeCoin;
}

