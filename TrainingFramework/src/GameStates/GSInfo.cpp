﻿#include "GSInfo.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
extern bool isGameOver;

GSInfo::GSInfo()
{

}


GSInfo::~GSInfo()
{
}



void GSInfo::Init()
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



	//text game title score
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Adriana");
	std::shared_ptr<Text> m_Text_gameName1 = std::make_shared< Text>(shader, font, "THONG TIN", TEXT_COLOR::RED, 3.0);
	m_Text_gameName1->Set2DPosition(Vector2(screenWidth / 2 - 80, 50));
	m_Text_gameName.push_back(m_Text_gameName1);

	//text game title highscore 1
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	font = ResourceManagers::GetInstance()->GetFont("Adriana");
	m_Text_gameName1 = std::make_shared< Text>(shader, font, "Tac gia : Bui Minh Tuan", TEXT_COLOR::RED, 2.0);
	m_Text_gameName1->Set2DPosition(Vector2(screenWidth / 2 - 140, 130));
	m_Text_gameName.push_back(m_Text_gameName1);

	//text game title highscore 1
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	font = ResourceManagers::GetInstance()->GetFont("Adriana");
	m_Text_gameName1 = std::make_shared< Text>(shader, font, "Cam on anh Hoang, anh Hung", TEXT_COLOR::RED, 2.0);
	m_Text_gameName1->Set2DPosition(Vector2(screenWidth / 2 - 173, 230));
	m_Text_gameName.push_back(m_Text_gameName1);

	//text game title highscore 1
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	font = ResourceManagers::GetInstance()->GetFont("Adriana");
	m_Text_gameName1 = std::make_shared< Text>(shader, font, "Cung cac ban thuc tap da giup em hoan thanh game nay", TEXT_COLOR::RED, 2.0);
	m_Text_gameName1->Set2DPosition(Vector2(screenWidth / 2 - 325, 260));
	m_Text_gameName.push_back(m_Text_gameName1);
}

void GSInfo::Exit()
{
}


void GSInfo::Pause()
{

}

void GSInfo::Resume()
{

}



void GSInfo::HandleEvents()
{

}

void GSInfo::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSInfo::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSInfo::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSInfo::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	for (auto it : m_Text_gameName) {
		it->Draw();
	}
}