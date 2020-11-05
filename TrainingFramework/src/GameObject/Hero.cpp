#include "Hero.h"


Hero::Hero(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{

}
Hero::~Hero()
{
}

