#pragma once

#include "State.h"

class GameStateLevelSelection : public State
{

public:

	enum EState
	{
		IDLE,
		ANIM_INTRO_ENTERED,
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

	EState		m_eCurrentState;
	float		m_fStateTime;

	ShObject * m_pScreenObject;

	ShEntity2 * m_pPressedButton;

	ShEntity2 * m_pButtonPrevious;
	ShEntity2 * m_pButtonNext;

	ShEntity2 * m_apThumbnails [9];
};
