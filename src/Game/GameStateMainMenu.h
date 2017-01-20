#pragma once

#include "State.h"

class GameStateMainMenu : public State
{

public:

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

private:

};
