#include "GSHelp.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
extern bool isGameOver;

GSHelp::GSHelp()
{

}


GSHelp::~GSHelp()
{
}



void GSHelp::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);


	texture = ResourceManagers::GetInstance()->GetTexture("Down");
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_Down = std::make_shared<Sprite2D>(model, shader, texture);
	m_Down->Set2DPosition(screenWidth / 2 - 60, 215);
	m_Down->SetSize(35,37);

	texture = ResourceManagers::GetInstance()->GetTexture("Up");
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_Up = std::make_shared<Sprite2D>(model, shader, texture);
	m_Up->Set2DPosition(screenWidth / 2 - 45, 115);
	m_Up->SetSize(35, 39);

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
	std::shared_ptr<Text> m_Text_gameName1 = std::make_shared< Text>(shader, font, "TRO GIUP", TEXT_COLOR::RED, 3.0);
	m_Text_gameName1->Set2DPosition(Vector2(screenWidth / 2 - 80, 50));
	m_Text_gameName.push_back(m_Text_gameName1);

	//text game title highscore 1
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	font = ResourceManagers::GetInstance()->GetFont("Adriana");
	m_Text_gameName1 = std::make_shared< Text>(shader, font, "Su dung phim ", TEXT_COLOR::RED, 1.8);
	m_Text_gameName1->Set2DPosition(Vector2(screenWidth / 2 - 250, 130));
	m_Text_gameName.push_back(m_Text_gameName1);

	//text game title highscore 1
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	font = ResourceManagers::GetInstance()->GetFont("Adriana");
	m_Text_gameName1 = std::make_shared< Text>(shader, font, "de an tien,", TEXT_COLOR::RED, 1.8);
	m_Text_gameName1->Set2DPosition(Vector2(screenWidth / 2 -15, 130));
	m_Text_gameName.push_back(m_Text_gameName1);

	//text game title highscore 1
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	font = ResourceManagers::GetInstance()->GetFont("Adriana");
	m_Text_gameName1 = std::make_shared< Text>(shader, font, "dong thoi co the su dung de ne tranh vat can", TEXT_COLOR::RED, 1.8);
	m_Text_gameName1->Set2DPosition(Vector2(screenWidth / 2 - 250, 160));
	m_Text_gameName.push_back(m_Text_gameName1);

	//text game title highscore 1
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	font = ResourceManagers::GetInstance()->GetFont("Adriana");
	m_Text_gameName1 = std::make_shared< Text>(shader, font, "Su dung phim ", TEXT_COLOR::RED, 1.8);
	m_Text_gameName1->Set2DPosition(Vector2(screenWidth / 2 - 250, 230));
	m_Text_gameName.push_back(m_Text_gameName1);

	//text game title highscore 1
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	font = ResourceManagers::GetInstance()->GetFont("Adriana");
	m_Text_gameName1 = std::make_shared< Text>(shader, font, "de tranh con chim bay den", TEXT_COLOR::RED, 1.8);
	m_Text_gameName1->Set2DPosition(Vector2(screenWidth / 2 - 20, 230));
	m_Text_gameName.push_back(m_Text_gameName1);
	
}

void GSHelp::Exit()
{
}


void GSHelp::Pause()
{

}

void GSHelp::Resume()
{

}



void GSHelp::HandleEvents()
{

}

void GSHelp::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSHelp::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSHelp::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
//	m_Down->Update(deltaTime);
//	m_Up->Update(deltaTime);
}

void GSHelp::Draw()
{
	m_BackGround->Draw();
	m_Down->Draw();
	m_Up->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	for (auto it : m_Text_gameName) {
		it->Draw();
	}
	
}