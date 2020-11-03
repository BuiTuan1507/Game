#include "GSPlay.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "SpriteAnimation.h"
extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("123");
	auto hero = ResourceManagers::GetInstance()->GetTexture("hero");
	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	m_Hero = std::make_shared<Sprite2D>(model, shader, hero);
	m_Hero->Set2DPosition(50, 360);
	m_Hero->SetSize(35, 55);



	texture = ResourceManagers::GetInstance()->GetTexture("button_back");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(700, 70);
	button->SetSize(150, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
	});
	m_listButton.push_back(button);

	// Animation
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("run");
	std::shared_ptr<SpriteAnimation> obj = std::make_shared<SpriteAnimation>(model, shader, texture, 10, 0.08f);
	obj->Set2DPosition(200, 240);
	obj->SetSize(52, 52);
	m_listSpriteAnimations.push_back(obj);


	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared< Text>(shader, font, "score: 10", TEXT_COLOR::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));
}

void GSPlay::Exit()
{

}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{

}


void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	Vector2 oldPostion = m_Hero->Get2DPosition();
	Vector2 oldBackground = m_BackGround->Get2DPosition();
	//m_Hero->HandKeyEvents(key, bIsPressed);
	switch (key)
	{
	case 40://xuong
		m_Hero->Set2DPosition(oldPostion.x , oldPostion.y+5);
	break;
	case 39://phai
		m_Hero->Set2DPosition(oldPostion.x+5, oldPostion.y );
	
		break;
	case 37://trai
		m_Hero->Set2DPosition(oldPostion.x - 5, oldPostion.y);
		break;
	case 38://len
		m_Hero->Set2DPosition(oldPostion.x, oldPostion.y - 5);
		break;
	}
	
	
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSPlay::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	m_Hero->Update(deltaTime);
	Vector2 newPost = m_BackGround->Get2DPosition();
	int deltaMove = newPost.x - screenWidth/2;
	m_BackGround->Set2DPosition(newPost.x-1, newPost.y);
	//if (newPost.x -  screenWidth/2 > 0){
		//m_BackGround->Set2DPosition(oldPost.x - deltaMove, oldPost.y);
	//}
	//else
	//{
		//m_BackGround->Set2DPosition(oldPost.x - deltaMove +screenWidth/2 , oldPost.y);
	//}
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	for (auto obj : m_listSpriteAnimations)
	{
		obj->Update(deltaTime);
	}
}

void GSPlay::Draw()
{
	m_BackGround->Draw();
	m_score->Draw();
	m_Hero->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	//for (auto obj : m_listSpriteAnimations)
	//{
		//obj->Draw();
	//}
}

void GSPlay::SetNewPostionForBullet()
{
}