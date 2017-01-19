#pragma once

#include "State.h"

class Game
{

public:

	enum EState
	{
		MENU,
		MAX_GAME_STATES
	};

	static Game & instance (void)
	{
		if (nullptr == instance_)
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

	// Get State
	State *	get(EState state)
	{
		switch (state)
		{
			case MENU:
			{
				return(nullptr); // FIXME
			}
			break;

			default:
			{
				return((State*)0); // this should never happen
			}
		}
	}

private:

	Game	(void);

	static Game * instance_;

	State *						m_aStates [MAX_GAME_STATES];
	int							m_iCurrentState;

};
