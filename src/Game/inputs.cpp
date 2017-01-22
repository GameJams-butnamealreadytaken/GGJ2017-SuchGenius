#include "inputs.h"

#include "Game.h"

/**
 * @brief OnTouchDown
 * @param iTouch
 * @param positionX
 * @param positionY
 */
void OnTouchDown(int iTouch, float positionX, float positionY)
{
	if (0 == iTouch)
	{
		CShVector2 pos(positionX, positionY);
		Game & game = Game::instance();
		game.touchBegin(pos);
	}
}

/**
 * @brief OnTouchUp
 * @param iTouch
 * @param positionX
 * @param positionY
 */
void OnTouchUp(int iTouch, float positionX, float positionY)
{
	if (0 == iTouch)
	{
		CShVector2 pos(positionX, positionY);
		Game & game = Game::instance();
		game.touchEnd(pos);
	}
}

/**
 * @brief OnTouchMove
 * @param iTouch
 * @param positionX
 * @param positionY
 */
void OnTouchMove(int iTouch, float positionX, float positionY)
{
	if (0 == iTouch)
	{
		CShVector2 pos(positionX, positionY);
		Game & game = Game::instance();
		game.touchMove(pos);
	}
}

Inputs::Inputs(void)
: m_isRestarting(false)
, m_isPressEnter(false)
{
}

Inputs::~Inputs(void)
{
}

void Inputs::Initialize(ShUser * pUser)
{
	m_pUser = pUser;
}

void Inputs::Release(void)
{
}

void Inputs::Update(void)
{
	if (shNULL != m_pUser)
	{
		m_isPressEnter = ShUser::HasTriggeredAction(m_pUser, CShIdentifier("validate"));
		m_isRestarting = ShUser::HasTriggeredAction(m_pUser, CShIdentifier("reset"));
	}
}

bool Inputs::IsRestarting(void)
{
	return(m_isRestarting);
}

bool Inputs::IsPressEnter(void)
{
	return(m_isPressEnter);
}
