#pragma once

#include "State.h"
#include "GameStateMainMenu.h"
#include "GameStateLevelSelection.h"
#include "GameStateGame.h"

class Game
{

public:

	enum EState
	{
		MAIN_MENU,
		LEVEL_SELECTION,
		GAME_LEVEL,

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

	GameStateMainMenu		m_stateMainMenu;
	GameStateLevelSelection	m_stateLevelSelection;
	GameStateGame			m_stateGame;

	bool					m_bMuted;
};
