#pragma once

void OnTouchDown(int iTouch, float positionX, float positionY);
void OnTouchUp(int iTouch, float positionX, float positionY);
void OnTouchMove(int iTouch, float positionX, float positionY);

class ShUser;

class Inputs
{
public:
	explicit	 Inputs(void);
	virtual		~Inputs(void);

	void		Initialize		(ShUser * pUser);
	void		Release			(void);

	void		Update			(void);

	bool		IsRestarting	(void);
	bool		IsPressEnter	(void);

private:
	ShUser *	m_pUser;

	bool		m_isRestarting;
	bool		m_isPressEnter;
};

