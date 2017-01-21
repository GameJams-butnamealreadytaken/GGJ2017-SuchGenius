#pragma once

#include "State.h"

class GameStateMainMenu : public State
{

public:

	enum EState
	{
		ANIM_INTRO_ENTERED,
		IDLE,
		ANIM_OUTRO_LEVELS,
	};

	explicit	GameStateMainMenu	(void);
	virtual		~GameStateMainMenu	(void);

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

protected:

	bool		load				(void);
	bool		unload				(void);

	void		setState			(EState eState);

private:

	EState		m_eCurrentState;
	float		m_fStateTime;

	ShObject * m_pScreenObject;

	ShEntity2 * m_pPressedButton;

	ShEntity2 * m_pButtonPlay;
	ShEntity2 * m_pButtonSound;
	ShEntity2 * m_pButtonLevels;
	ShEntity2 * m_pButtonInfo;

	ShEntity2 * m_pIconSoundOn;
	ShEntity2 * m_pIconSoundOff;

	ShEntity2 * m_pTitleEntity;

};
