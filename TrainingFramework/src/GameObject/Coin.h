
#pragma once 
#include "SpriteAnimation.h"

class Coin : public SpriteAnimation
{
public:
	Coin(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime);
	~Coin();

	

public:
	int activeCoin = 1;
	void setActive(int activeCoin) ;
	int getActive() ;


};

