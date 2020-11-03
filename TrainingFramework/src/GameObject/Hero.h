#pragma once 
#include "Sprite2D.h"

class Hero : public Sprite2D
{
public:
	Hero(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~Hero();
	void	SetOnClick(void(*pBtClick)());
	void	HandleTouchEvents(GLint x, GLint y, bool bIsPressed);
	bool	IsHandle();

private:
	void(*m_pBtClick)();
	bool	m_isHandle;

};

