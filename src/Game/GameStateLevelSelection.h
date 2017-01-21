#pragma once

#include "State.h"

#define MAX_PAGE 2

class GameStateLevelSelection : public State
{

public:

	enum EState
	{
		ANIM_INTRO_ENTERED,
		IDLE,
		ANIM_OUTRO_MAIN_MENU,
	};

	explicit	GameStateLevelSelection		(void);
	virtual		~GameStateLevelSelection	(void);

	void		init						(void) SH_ATTRIBUTE_OVERRIDE;
	void		release						(void) SH_ATTRIBUTE_OVERRIDE;

	void		entered						(void) SH_ATTRIBUTE_OVERRIDE;
	void		exiting						(void) SH_ATTRIBUTE_OVERRIDE;

	void		obscuring					(void) SH_ATTRIBUTE_OVERRIDE;
	void		revealed					(void) SH_ATTRIBUTE_OVERRIDE;

	void		update						(float dt) SH_ATTRIBUTE_OVERRIDE;

	void		touchBegin					(const CShVector2 & pos) SH_ATTRIBUTE_OVERRIDE;
	void		touchEnd					(const CShVector2 & pos) SH_ATTRIBUTE_OVERRIDE;
	void		touchMove					(const CShVector2 & pos) SH_ATTRIBUTE_OVERRIDE;

	void		prepareAnim					(ShObject * pParent);

private:

	void		setState					(EState eState);

	void		DisplayCurrentPage			(void);

private:

	EState		m_eCurrentState;
	float		m_fStateTime;

	ShEntity2 * m_pPressedButton;

	ShObject *	m_pScreenObject;

	ShEntity2 * m_pBackButton;

	ShEntity2 * m_pButtonPrevious;
	ShEntity2 * m_pButtonNext;

	ShEntity2 * m_apThumbnails [9];
	ShEntity2 * m_apLevelIcon  [MAX_PAGE][9];

	int			m_iLastPageID;
	int			m_iCurrentPageID;
};
