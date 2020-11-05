#include "Obstacle.h"


Obstacle::Obstacle(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{

}
Obstacle::~Obstacle()
{
}

