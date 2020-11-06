#pragma once
#include "gamestatebase.h"
#include "GameButton.h"

class Sprite2D;
class Sprite3D;
class Text;
class SpriteAnimation;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);

	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();


	void SetNewPostionForBullet();
	void giveCoin();
	void Jump();

private:

	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Sprite2D> m_BackGround1;
	std::shared_ptr<Sprite2D> m_BackGround2;
	std::shared_ptr<Sprite2D> m_Hero;
	std::shared_ptr<Text>  m_score;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<SpriteAnimation > heroJump;
	std::shared_ptr<SpriteAnimation > heroPopState;

	std::vector < std::shared_ptr<SpriteAnimation>> m_listActiveAnimations;
	std::vector < std::shared_ptr<SpriteAnimation>> m_listSpriteAnimations;
	std::vector < std::shared_ptr<SpriteAnimation>> m_listSpriteAnimations1;
	std::vector < std::shared_ptr<SpriteAnimation>> m_listSpriteAnimations2;
	std::vector < std::shared_ptr<SpriteAnimation>> m_listSpriteAnimations3;
	//std::vector <std::vector < std::shared_ptr<SpriteAnimation>>> m_listCoinAnimations;
	std::list<std::shared_ptr<Sprite2D>> m_listCoin;

};

