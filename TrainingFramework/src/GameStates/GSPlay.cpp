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
int score = 0;
bool keyUP = false;
int stateHero = 0;
int timeJump = 50;
int deltaMove = 0;


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
	auto hero = ResourceManagers::GetInstance()->GetTexture("bbc1");
	auto coin = ResourceManagers::GetInstance()->GetTexture("coin_Game");
	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//Background1
	m_BackGround1 = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround1->Set2DPosition(3/2 * screenWidth , screenHeight / 2);
	m_BackGround1->SetSize(screenWidth, screenHeight);
	//Hero
	m_Hero = std::make_shared<Sprite2D>(model, shader, hero);
	m_Hero->Set2DPosition(350, 380);
	m_Hero->SetSize(21, 22);

	
	//button back
	texture = ResourceManagers::GetInstance()->GetTexture("button_back");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(700, 70);
	button->SetSize(150, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
	});
	m_listButton.push_back(button);

	
	//coin1
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("coin1");
	std::shared_ptr<SpriteAnimation> obj = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 0.1f);
	obj->Set2DPosition(130, 330);
	obj->SetSize(20, 20);
	m_listSpriteAnimations1.push_back(obj);
	//m_listCoinAnimations[0].push_back(obj);
	//coin
	obj = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 0.1f);
	obj->Set2DPosition(180, 330);
	obj->SetSize(20, 20);
	m_listSpriteAnimations1.push_back(obj);
	//m_listCoinAnimations[1].push_back(obj);
	// Animation
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("run");
	obj = std::make_shared<SpriteAnimation>(model, shader, texture, 10, 0.1f);
	obj->Set2DPosition(50, 360);
	obj->SetSize(52, 52);
	m_listSpriteAnimations.push_back(obj);
	m_listActiveAnimations.push_back(obj);

	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("jump");
	heroJump = std::make_shared<SpriteAnimation>(model, shader, texture, 10, 0.1f);
	heroJump->Set2DPosition(250, 360);
	heroJump->SetSize(52, 52);
	m_listSpriteAnimations.push_back(obj);

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared< Text>(shader, font, std::to_string(score), TEXT_COLOR::RED, 1.0);
	m_score->Set2DPosition(Vector2(20, 25));
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
	Vector2 oldPostion = m_listSpriteAnimations[0]->Get2DPosition();
	Vector2 oldBackground = m_BackGround->Get2DPosition();
	//m_Hero->HandKeyEvents(key, bIsPressed);
	if ((key == KEY_LEFT) && (bIsPressed == true))
	{
		m_listSpriteAnimations[0]->Set2DPosition(oldPostion.x - 5, oldPostion.y);
	
	}
	if ((key == KEY_RIGHT) && (bIsPressed == true))
	{
		m_listSpriteAnimations[0]->Set2DPosition(oldPostion.x + 5, oldPostion.y);
	}
	if ((key == KEY_UP) && (bIsPressed == true))
	{
		m_listActiveAnimations.pop_back();
		Vector2 jumpPosition =  m_listSpriteAnimations[0]->Get2DPosition();
		heroJump->Set2DPosition(jumpPosition.x , jumpPosition.y - 30);
		m_listActiveAnimations.push_back(heroJump);
		stateHero = 1;
		
		
	

	}
	if ((key == KEY_DOWN) && (bIsPressed == true))
	{
		m_listSpriteAnimations[0]->Set2DPosition(oldPostion.x, oldPostion.y + 5);
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
	m_BackGround1->Update(deltaTime);
	m_score->Update(deltaTime);
	Vector2 p_Background = m_BackGround->Get2DPosition();
	Vector2 p_Background1 = m_BackGround1->Get2DPosition();
	
	if (p_Background1.x - deltaMove > -screenWidth / 2) {
		m_BackGround1->Set2DPosition(p_Background1.x - deltaMove, p_Background1.y);
	}
	else
	{
		m_BackGround1->Set2DPosition(p_Background1.x - deltaMove + 2 * screenWidth, p_Background1.y);
	}

	 //setup state hero
	 if ((stateHero == 1) && (timeJump > 0)){
		 timeJump = timeJump - deltaTime;
	 }
	 else {
		 Vector2 runPosition = m_listSpriteAnimations[0]->Get2DPosition();
		// m_listSpriteAnimations[0]->Set2DPosition(runPosition.x + 10, runPosition.y);
		 m_listActiveAnimations.pop_back();
		 m_listActiveAnimations.push_back(m_listSpriteAnimations[0]);
		 stateHero = 0;
		 timeJump = 50;
	 }
	 // get coin
	 Vector2 positionHero = m_listActiveAnimations[0]->Get2DPosition();
	 for (auto it : m_listSpriteAnimations1) {
		 Vector2 positionCoin = it->Get2DPosition();
		 int p = positionHero.x - positionCoin.x;
		 if ((p<25) && (p>-25) && (positionHero.y == positionCoin.y))
		 {
			 score = score + 1;
			 //m_listSpriteAnimations1.pop_back();
			 printf("a");
			 
		 }
	 }

	for (auto it1 : m_listButton)
	{
		it1->Update(deltaTime);
	}
	
	for (auto it : m_listActiveAnimations) {
			it->Update(deltaTime);
	}
	for (auto it : m_listSpriteAnimations1) {
	it->Update(deltaTime);
	}

	

}

void GSPlay::Draw()
{
	m_BackGround->Draw();
	m_BackGround1->Draw();
	
	m_score->Draw();
	m_Hero->Draw();
	for (auto it1 : m_listButton)
	{
		it1->Draw();
	}
	
	for (auto it : m_listSpriteAnimations1) {
			it->Draw();
	}
	
	
	for (auto obj : m_listActiveAnimations)
	{
		obj->Draw();
	}
	
}

void GSPlay::SetNewPostionForBullet()
{
}
void GSPlay::giveCoin() {
	
}