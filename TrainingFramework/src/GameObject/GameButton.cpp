#include "GameButton.h"


GameButton::GameButton(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{
	m_pBtClick = nullptr;
	m_isHandle = false;
	m_click = false;
	m_Active = true;
}

GameButton::~GameButton()
{
}

void GameButton::SetOnClick(void(*pBtClickFun)())
{
	m_pBtClick = pBtClickFun;
}

void GameButton::HandleTouchEvents(GLint x, GLint y, bool bIsPressed)
{
	m_isHandle = false;
	if ((x > m_Vec2DPos.x  - m_iWidth/2) && (x < m_Vec2DPos.x + m_iWidth / 2) && (y > m_Vec2DPos.y - m_iHeight / 2) && (y < m_Vec2DPos.y + m_iHeight / 2))
	{
		m_pBtClick();
		m_isHandle = true;
	}
}

bool GameButton::IsHandle()
{
	return m_isHandle;
}
bool GameButton::IsClick(bool bIsPressed) 
{
	if (bIsPressed == true) {
		m_click = true;
	}
	else
	{
		m_click = false;
	}
	return m_click;
}

void GameButton::setActive(bool isActive)
{
	m_Active = isActive;
}

bool GameButton::getActive()
{
	return m_Active;
}
