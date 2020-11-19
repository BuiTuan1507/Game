#include "GSGameOver.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
using std::ofstream;
extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
extern int score;

int cc;
GSGameOver::GSGameOver()
{
	
	ifstream file ("score.txt");
	ofstream file1("score.txt");
	
	
	
	//file write
	file1 << score;
	file.close();
	file1.close();
}


GSGameOver::~GSGameOver()
{
}



void  GSGameOver::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//play button
	texture = ResourceManagers::GetInstance()->GetTexture("back");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(700, 50);
	button->SetSize(70, 70);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
	});
	m_listButton.push_back(button);
	//option button
	auto texture1 = ResourceManagers::GetInstance()->GetTexture("GOV");
	auto shader1 = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_GameOver = std::make_shared<Sprite2D>(model, shader1, texture1);
	m_GameOver->Set2DPosition(400 ,100);
	m_GameOver->SetSize(300, 300);

	//text game title score
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	std::shared_ptr<Text> m_Text_gameName1 = std::make_shared< Text>(shader, font, "SCORE:", TEXT_COLOR::RED, 1.4);
	m_Text_gameName1->Set2DPosition(Vector2(screenWidth / 2 - 120, 300));
	m_Text_gameName.push_back(m_Text_gameName1);

	//text game title highscore 1
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared< Text>(shader, font, std::to_string(score), TEXT_COLOR::RED, 1.4);
	m_score->Set2DPosition(Vector2(screenWidth/2 + 60, 300));

}

void  GSGameOver::Exit()
{
}


void GSGameOver::Pause()
{

}

void  GSGameOver::Resume()
{

}




void  GSGameOver::HandleEvents()
{

}

void GSGameOver::HandleKeyEvents(int key, bool bIsPressed)
{

}

void  GSGameOver::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void  GSGameOver::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void  GSGameOver::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	for (auto it : m_Text_gameName) {
		it->Draw();
	}
	m_score->Draw();
	m_GameOver->Draw();
}