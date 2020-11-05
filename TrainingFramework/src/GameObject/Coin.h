
#pragma once 
#include "Sprite2D.h"

class Coin : public Sprite2D
{
public:
	Coin(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~Coin();


private:



};

