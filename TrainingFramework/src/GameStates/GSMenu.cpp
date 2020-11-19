 #include "GSMenu.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
bool isMusic;
GSMenu::GSMenu()
{
	isMusic = true;
}


GSMenu::~GSMenu()
{
}



void GSMenu::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//play button
	texture = ResourceManagers::GetInstance()->GetTexture("b_play");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 130);
	button->SetSize(126, 70);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
	});
	m_listButton.push_back(button);
	//option button
	texture = ResourceManagers::GetInstance()->GetTexture("INFO");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 210);
	button->SetSize(126, 71);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Info);
	});
	m_listButton.push_back(button);

	//exit button
	texture = ResourceManagers::GetInstance()->GetTexture("112");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 290);
	button->SetSize(126, 71);
	button->SetOnClick([]() {
		exit(0);
	});
	m_listButton.push_back(button);

	//onMusic button
	texture = ResourceManagers::GetInstance()->GetTexture("onMusic");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2-150, 380);
	button->SetSize(60, 60);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->CurrentState()->Resume();
	});
	m_listButton.push_back(button);

	//offMusic button
	texture = ResourceManagers::GetInstance()->GetTexture("offMusic");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2 - 150, 380);
	button->SetSize(60, 60);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->CurrentState()->Pause();
	});
	m_listButton.push_back(button);

	//highScore button
	texture = ResourceManagers::GetInstance()->GetTexture("highScore");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2 - 0, 380);
	button->SetSize(60, 60);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_HighScore);
	});
	m_listButton.push_back(button);

	//onMusic button
	texture = ResourceManagers::GetInstance()->GetTexture("help");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2 + 150 , 380);
	button->SetSize(60, 60);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Help);
	});
	m_listButton.push_back(button);

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Adriana");
	m_Text_gameName = std::make_shared< Text>(shader, font, "RUNNING MAN", TEXT_COLOR::GREEN, 3.5);
	m_Text_gameName->Set2DPosition(Vector2(screenWidth / 2 - 130, 65));

}

void GSMenu::Exit()
{
}


void GSMenu::Pause()
{
	//isPauseGame = true;
	isMusic = false;
	m_listButton[4]->setActive(false);
	m_listButton[3]->setActive(true);
	//ResourceManagers::GetInstance()->PauseSound("2");
}

void GSMenu::Resume()
{
	isMusic = true;
	//isPauseGame = false;
	m_listButton[4]->setActive(true);
	m_listButton[3]->setActive(false);
	//ResourceManagers::GetInstance()->PlaySound("2");
}


void GSMenu::HandleEvents()
{

}

void GSMenu::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSMenu::HandleTouchEvents(int x, int y, bool bIsPressed)
{

	for (auto it : m_listButton)
	{
		if (it->getActive() && (bIsPressed == true))
		{
			(it)->HandleTouchEvents(x, y, bIsPressed);
			if ((it)->IsHandle()) break;
		}

	}
}

void GSMenu::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSMenu::Draw()
{
	m_BackGround->Draw();
	for (auto it1 : m_listButton)
	{

		if (it1->getActive())
		{
			it1->Draw();
		}
	}
	m_Text_gameName->Draw();
}