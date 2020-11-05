#pragma once 
#include "Sprite2D.h"

class Hero : public Sprite2D
{
public:
	Hero(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~Hero();
	

private:
	
	

};

