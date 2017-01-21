#pragma once

#include "State.h"

class GameStateWin : public State
{

public:

	enum EState
	{
		ANIM_INTRO_ENTERED,
		IDLE,
	};

	explicit	GameStateWin		(void);
	virtual		~GameStateWin		(void);

	void		init				(void) SH_ATTRIBUTE_OVERRIDE;
	void		release				(void) SH_ATTRIBUTE_OVERRIDE;

	void		entered				(void) SH_ATTRIBUTE_OVERRIDE;
	void		exiting				(void) SH_ATTRIBUTE_OVERRIDE;

	void		obscuring			(void) SH_ATTRIBUTE_OVERRIDE;
	void		revealed			(void) SH_ATTRIBUTE_OVERRIDE;

	void		update				(float dt) SH_ATTRIBUTE_OVERRIDE;

	void		touchBegin			(const CShVector2 & pos) SH_ATTRIBUTE_OVERRIDE;
	void		touchEnd			(const CShVector2 & pos) SH_ATTRIBUTE_OVERRIDE;
	void		touchMove			(const CShVector2 & pos) SH_ATTRIBUTE_OVERRIDE;

private:

	EState		m_eCurrentState;
	float		m_fStateTime;

	ShEntity2 * m_pPressedButton;

	ShEntity2 * m_pButtonMenu;
	ShEntity2 * m_pButtonRetry;
	ShEntity2 * m_pButtonNext;

	ShEntity2 * m_pPopupBackgroundEntity;
	ShEntity2 * m_pPopupEntity;

	int			m_iClicCount;

};
