#include "GSGameOver.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
using std::ofstream;
extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
extern int score;
int highScore[3] = {0,0,0};
int cc;
GSGameOver::GSGameOver()
{
	int  i = 0;
	int h;
	ifstream file ("score.txt");
	ofstream file1("score.txt");
	//file.open("score.txt",ios::in);
	if(file.is_open())
	{
		file >> highScore[0] >> highScore[1] >> highScore[2];
		if (score > highScore[0])
		{
			highScore[0] = score;
			highScore[1] = highScore[0];
			highScore[2] = highScore[1];
		}
		if ((score > highScore[1]) && (score < highScore[0]))
		{
			highScore[1] = score;
			highScore[2] = highScore[1];
		}
		if ((score > highScore[2]) && (score < highScore[1]))
		{
			
			highScore[2] = score;
		}

		
		
	}
	
	
	//file write
	file1 << highScore[0] << " " << highScore[1] << " "<< highScore[2] << endl;
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
	texture = ResourceManagers::GetInstance()->GetTexture("button_back");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(700, 50);
	button->SetSize(200, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
	});
	m_listButton.push_back(button);
	//option button



	//text game title score
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	std::shared_ptr<Text> m_Text_gameName1 = std::make_shared< Text>(shader, font, "GAME OVER", TEXT_COLOR::RED, 2.0);
	m_Text_gameName1->Set2DPosition(Vector2(screenWidth / 2 -100, 120));
	m_Text_gameName.push_back(m_Text_gameName1);

	//text game title highscore 1
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared< Text>(shader, font, std::to_string(score), TEXT_COLOR::RED, 1.2);
	m_score->Set2DPosition(Vector2(screenWidth/2-80, 225));

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
}