#pragma once

#include "State.h"
#include "GameStateMainMenu.h"
#include "GameStateCredits.h"
#include "GameStateLevelSelection.h"
#include "GameStateGame.h"
#include "GameStateWin.h"

#include "GameSave.h"

extern PluginGGJ2017 * g_pInstance = shNULL;
extern ShUser *	g_pCurrentUser = shNULL;
extern Inputs * g_pInputs = shNULL;
extern GameSave * g_pGameSave = shNULL;

class Game
{

public:

	enum EState
	{
		MAIN_MENU,
		LEVEL_SELECTION,
		GAME_LEVEL,
		GAME_WIN,
		CREDITS,

		MAX_GAME_STATES
	};

	static Game & instance (void)
	{
		if (shNULL == instance_)
		{
			instance_ = new Game();
		}

		return(*instance_);
	}

	void		initialize		(void);
	void		release			(void);

	void		update			(float dt);

	void		touchBegin		(const CShVector2 & pos);
	void		touchEnd		(const CShVector2 & pos);
	void		touchMove		(const CShVector2 & pos);

	void		push			(EState state);
	void		pop				(void);

	bool		toggleMute		(void);

	// Get State
	State *	get(EState state)
	{
		switch (state)
		{
			case MAIN_MENU:
			{
				return(&m_stateMainMenu);
			}
			break;

			case LEVEL_SELECTION:
			{
				return(&m_stateLevelSelection);
			}
			break;

			case GAME_LEVEL:
			{
				return(&m_stateGame);
			}
			break;

			case GAME_WIN:
			{
				return(&m_stateWin);
			}
			break;

			case CREDITS:
			{
				return(&m_stateCredits);
			}
			break;

			default:
			{
				return((State*)0); // this should never happen
			}
		}
	}

private:

	Game					(void);

	static Game *			instance_;

	State *					m_aStates [MAX_GAME_STATES];
	int						m_iCurrentState;

	GameStateCredits		m_stateCredits;
	GameStateMainMenu		m_stateMainMenu;
	GameStateLevelSelection	m_stateLevelSelection;
	GameStateGame			m_stateGame;
	GameStateWin			m_stateWin;

	bool					m_bMuted;

};
