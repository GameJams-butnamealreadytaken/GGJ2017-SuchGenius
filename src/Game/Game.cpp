#include "Game.h"

#include "ShSDK/ShSDK.h"

int g_nbMinPlay[9] = {1, 3, 2, 3, 2, 3, 2, 2, 2};

ShUser * g_pCurrentUser = shNULL;
Inputs * g_pInputs = shNULL;
GameSave * g_pGameSave = shNULL;

Game * Game::instance_ = shNULL;

/**
 * @brief Game::Game
 */
Game::Game(void) : m_iCurrentState(-1), m_bMuted(false)
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
	bool bLoaded = ShLevel::Load(CShIdentifier("background"));
	SH_ASSERT(bLoaded);

	get(MAIN_MENU)->init();
	get(LEVEL_SELECTION)->init();
	get(GAME_LEVEL)->init();
	get(GAME_WIN)->init();

	push(MAIN_MENU);
}

/**
 * @brief Game::release
 */
void Game::release(void)
{
	pop();

	get(GAME_LEVEL)->release();
	get(LEVEL_SELECTION)->release();
	get(MAIN_MENU)->release();
	get(GAME_WIN)->release();

	ShLevel::Release();
}

/**
 * @brief Game::update
 */
void Game::update(float dt)
{
	g_pInputs->Update();
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


/**
 * @brief Game::toggleMute
 * @return
 */
bool Game::toggleMute(void)
{
	m_bMuted = !m_bMuted;

	if (m_bMuted)
	{
		ShSound::SetGlobalVolume(0.0f);
	}
	else
	{
		ShSound::SetGlobalVolume(1.0f);
	}

	return(m_bMuted);
}
