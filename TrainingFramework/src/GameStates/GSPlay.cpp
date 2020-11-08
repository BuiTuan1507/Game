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
#include "Obstacle.h"
#include "Coin.h"
#include "GSGameOver.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
int score = 0;
bool keyUP = false;
bool eatCoin = false;
bool distanJump = false;
int stateHero = 0;
int timeJump = 10;
int deltaMove = 0;
int deltaJump = 0;
bool isGameOver = false;

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
	m_BackGround1->Set2DPosition(1.5 * screenWidth , screenHeight / 2);
	m_BackGround1->SetSize(screenWidth, screenHeight);
	//Obstaccle
	
	for (auto i = 0; i < 100; i++)
	{
		m_Obstacle = std::make_shared<Sprite2D>(model, shader, hero);
		m_Obstacle->SetSize(21, 22);
		m_Obstacle->Set2DPosition(150 * (i + 1), 380);
		m_listObstacle.push_back(m_Obstacle);
	}
	//button back
	texture = ResourceManagers::GetInstance()->GetTexture("button_back");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(700, 70);
	button->SetSize(150, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
	});
	m_listButton.push_back(button);

	for (int i = 0; i < 50; i++) 
	{
		shader = ResourceManagers::GetInstance()->GetShader("Animation");
		texture = ResourceManagers::GetInstance()->GetTexture("coin1");
		std::shared_ptr<Coin> obj = std::make_shared<Coin>(model, shader, texture, 6, 0.1f);
		obj->Set2DPosition(180*(i+1), 330);
		obj->SetSize(20, 20);
		m_listCoin1.push_back(obj);
	}
	//coin1
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("coin1");
	std::shared_ptr<Coin> obj1 = std::make_shared<Coin>(model, shader, texture, 6, 0.1f);
	obj1->Set2DPosition(100, 330);
	obj1->SetSize(20, 20);
	m_listCoin1.push_back(obj1);
	
	
	// Animation
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("run");
	std::shared_ptr<SpriteAnimation> obj = std::make_shared<SpriteAnimation>(model, shader, texture, 10, 0.1f);
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

	
	//ResourceManagers::GetInstance()->PlaySound("1");
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
		
		Jump();
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
	deltaJump = deltaTime;
	m_BackGround->Update(deltaTime);
	m_BackGround1->Update(deltaTime);
	
	Vector2 p_Background = m_BackGround->Get2DPosition();
	Vector2 p_Background1 = m_BackGround1->Get2DPosition();
	deltaMove = 50 * deltaTime;
	if (p_Background1.x - deltaMove > -screenWidth / 2) {
		m_BackGround1->Set2DPosition(p_Background1.x - deltaMove, p_Background1.y);
	}
	else
	{
		m_BackGround1->Set2DPosition(p_Background1.x - deltaMove + 2 * screenWidth, p_Background1.y);
	}
	if (p_Background.x - deltaMove > -screenWidth / 2) {
		m_BackGround->Set2DPosition(p_Background.x - deltaMove, p_Background.y);
	}
	else
	{
		m_BackGround->Set2DPosition(p_Background.x - deltaMove + 2 * screenWidth, p_Background.y);
	}

	 //setup state hero
	 if ((stateHero == 1) && (timeJump > 0)){
		 timeJump = timeJump - deltaTime;
		 Vector2 jumpP = m_listActiveAnimations[0]->Get2DPosition();
		 m_listActiveAnimations[0]->Set2DPosition(jumpP.x + 2, jumpP.y);
	 }
	 else {
		 Vector2 runPosition = m_listSpriteAnimations[0]->Get2DPosition();
		 if (distanJump == true) {
			 m_listSpriteAnimations[0]->Set2DPosition(runPosition.x + 20, runPosition.y);
			 distanJump = false;
		 }
		
		 m_listActiveAnimations.pop_back();
		 m_listActiveAnimations.push_back(m_listSpriteAnimations[0]);
		 stateHero = 0;
		 timeJump = 8;
	 }
	 // get coin
	 Vector2 positionHero = m_listActiveAnimations[0]->Get2DPosition();
	 for (auto it : m_listCoin1) {
		 Vector2 positionCoin = it->Get2DPosition();
		 int p = positionHero.x - positionCoin.x;
		 if ((p<25) && (p>-25) && (positionHero.y == positionCoin.y) && (eatCoin == true))
		 {
			 score = score + 10;
			 eatCoin = false;
			 //m_listSpriteAnimations1.pop_back();
			 
			 int activeCoin = it->getActive();
			 if (activeCoin == 1) {
				 activeCoin = 0;
			 }
			 it->setActive(activeCoin);
			 
			 printf("%d", activeCoin);
			 
		 }
	 }
	 // GameOver
	 for (auto it : m_listObstacle) {
		 Vector2 poistionObstacle = it->Get2DPosition();
		 int  p = positionHero.x - poistionObstacle.x;
		 if ((p < 10) && (p > -10) && ((poistionObstacle.y+20) == positionHero.y)) {
			 isGameOver = true;
			 printf("aa");
		 }
	 }
	 //setState GameOver
	 if (isGameOver) {
		 GameStateMachine::GetInstance()->PopState();
		 GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_GameOver);
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

	for (auto it : m_listObstacle) {
		Vector2 oldObstacle = it->Get2DPosition();
		it->Set2DPosition(oldObstacle.x - 50 * deltaTime, oldObstacle.y);
		it->Update(deltaTime);
	}
	for (auto it : m_listCoin1) {
		
			Vector2 oldCoin = it->Get2DPosition();
			it->Set2DPosition(oldCoin.x - 50 * deltaTime, oldCoin.y);
			it->Update(deltaTime);
		
		
	}

	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared< Text>(shader, font, std::to_string(score), TEXT_COLOR::RED, 1.0);
	m_score->Set2DPosition(Vector2(20, 25));

}

void GSPlay::Draw()
{
	m_BackGround->Draw();
	m_BackGround1->Draw();
	
	m_score->Draw();

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
	for (auto it : m_listObstacle) {
		it->Draw();
	}
	for (auto it : m_listCoin1) {
		if (it->activeCoin == 1) {
			it->Draw();
		}
		
	}
	
}

void GSPlay::SetNewPostionForBullet()
{
}
void GSPlay::giveCoin() {
	
}
void GSPlay::Jump() {
	m_listActiveAnimations.pop_back();
	Vector2 jumpPosition = m_listSpriteAnimations[0]->Get2DPosition();
	heroJump->Set2DPosition(jumpPosition.x, jumpPosition.y - 30);
	m_listActiveAnimations.push_back(heroJump);
	stateHero = 1;
	eatCoin = true;
	distanJump = true;
}