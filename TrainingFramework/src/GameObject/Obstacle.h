
#pragma once 
#include "Sprite2D.h"

class Obstacle : public Sprite2D
{
public:
	Obstacle(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~Obstacle();


private:



};

