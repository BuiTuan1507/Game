/*
#include "GSIntro.h"
#include "GSMenu.h"
*/
#include "GSPlay.h"
#include "GSIntro.h"
#include "GSMenu.h"
#include "GSHighScore.h"
#include "GSGameOver.h"
#include "GSInfo.h"
#include "GSHelp.h"
#include "GameStatebase.h"

std::shared_ptr<GameStateBase> GameStateBase::CreateState(StateTypes stt)
{
	std::shared_ptr<GameStateBase> gs = nullptr;
	switch (stt)
	{
	case STATE_INVALID:
		break;
	case STATE_Intro:
		gs = std::make_shared<GSIntro>();
		break;
	case STATE_Menu:
		gs = std::make_shared<GSMenu>();
		break;
	case STATE_Play:
		gs = std::make_shared<GSPlay>();
		break;
	case STATE_HighScore:
		gs = std::make_shared<GSHighScore>();
		break;
	case STATE_GameOver:
		gs = std::make_shared<GSGameOver>();
		break;
	case STATE_Info:
		gs = std::make_shared<GSInfo>();
		break;
	case STATE_Help:
		gs = std::make_shared<GSHelp>();

	default:
		break;
	}
	return gs;
}