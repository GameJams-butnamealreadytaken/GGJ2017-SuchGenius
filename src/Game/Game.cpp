#include "Game.h"

#include "ShSDK/ShSDK.h"

Game * Game::instance_ = shNULL;

/**
 * @brief Game::Game
 */
Game::Game(void) : m_iCurrentState(-1)
{
	for (int i = 0; i < MAX_GAME_STATES; ++i)
	{
		m_aStates[i] = shNULL;
	}
}

/**
 * @brief Game::initialize
 */
void Game::initialize(void)
{
	m_aStates[MAIN_MENU] = new GameStateMainMenu();
	SH_ASSERT(shNULL != m_aStates[MAIN_MENU]);
	m_aStates[MAIN_MENU]->init();

	m_aStates[GAME_LEVEL] = new GameStateGame();
	SH_ASSERT(shNULL != m_aStates[GAME_LEVEL]);
	m_aStates[GAME_LEVEL]->init();
	 
	push(MAIN_MENU);
}

/**
 * @brief Game::release
 */
void Game::release(void)
{
	m_aStates[m_iCurrentState]->release();
}

/**
 * @brief Game::update
 */
void Game::update(float dt)
{
	m_aStates[m_iCurrentState]->update(dt);
}

/**
 * @brief Game::touchBegin
 */
void Game::touchBegin(const CShVector2 & pos)
{
	CShVector2 scaled(pos); // FIXME

	m_aStates[m_iCurrentState]->touchBegin(scaled);
}

/**
 * @brief Game::touchEnd
 */
void Game::touchEnd(const CShVector2 & pos)
{
	CShVector2 scaled(pos); // FIXME

	m_aStates[m_iCurrentState]->touchEnd(scaled);
}

/**
 * @brief Game::touchMove
 */
void Game::touchMove(const CShVector2 & pos)
{
	CShVector2 scaled(pos); // FIXME

	m_aStates[m_iCurrentState]->touchMove(scaled);
}

/**
 * @brief Game::push
 * @param state
 */
void Game::push(EState state)
{
	SH_ASSERT(m_iCurrentState < MAX_GAME_STATES);

	if (m_iCurrentState >= 0)
	{
		m_aStates[m_iCurrentState]->obscuring();
	}

	++m_iCurrentState;

	m_aStates[m_iCurrentState] = get(state);

	m_aStates[m_iCurrentState]->entered();
}

/**
 * @brief Game::pop
 */
void Game::pop(void)
{
	SH_ASSERT(m_iCurrentState >= 0);

	m_aStates[m_iCurrentState]->exiting();

#if SH_DEBUG
	m_aStates[m_iCurrentState] = nullptr;
#endif

	--m_iCurrentState;

	if (m_iCurrentState >= 0)
	{
		m_aStates[m_iCurrentState]->revealed();
	}
}

