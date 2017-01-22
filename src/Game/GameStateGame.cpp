#include "GameStateGame.h"

#include "Game.h"

/**
* @brief GameStateGame::Constructor
*/
GameStateGame::GameStateGame(void)
: m_pPressedButton(shNULL)
, m_pHomeButton(shNULL)
, m_pRestartButton(shNULL)
{
	// ...
}

/**
* @brief GameStateGame::Destructor
*/
GameStateGame::~GameStateGame(void)
{
	// ...
}

/**
* @brief GameStateGame::Initialize
*/
void GameStateGame::init(void)
{
	// ...
}

/**
* @brief GameStateGame::Release
*/
void GameStateGame::release(void)
{
	// ...
}

/**
* @brief GameStateGame::entered
*/
void GameStateGame::entered(void)
{
	load();
}

/**
* @brief GameStateGame::exiting
*/
void GameStateGame::exiting(void)
{
	unload();
}

/**
* @brief GameStateGame::obscuring
*/
void GameStateGame::obscuring(void)
{
	// ...
}

/**
* @brief GameStateGame::obscuring
*/
void GameStateGame::revealed(void)
{
	unload();
	load();
}

/**
 * @brief GameStateGame::load
 */
void GameStateGame::load(void)
{
	CShString strLevelName = CShString("level_0") + CShString::FromInt(GetCurrentLevel());
	CShIdentifier levelIdentifier(strLevelName);
	bool loading = ShLevel::Load(levelIdentifier);

	g_pGameSave->SetLastLevelPlayed(GetCurrentLevel());

	if (!loading)
	{
		Game & game = Game::instance();
		game.pop();
		game.push(Game::CREDITS);
		return;
	}

	SH_ASSERT(loading);

	m_pRestartButton = ShEntity2::Find(levelIdentifier, CShIdentifier("button_retry"));
	SH_ASSERT(shNULL != m_pRestartButton);

	m_pHomeButton = ShEntity2::Find(levelIdentifier, CShIdentifier("button_home"));
	SH_ASSERT(shNULL != m_pHomeButton);
}

/**
 * @brief GameStateGame::unload
 */
void GameStateGame::unload(void)
{
	ShLevel::Release();
}

/**
* @brief GameStateGame::Release
*/
void GameStateGame::update(float dt)
{
	if (g_pInputs->IsRestarting())
	{
		g_pInstance->Reset();
	}

	if (g_pInstance->IsWon())
	{
		Game & game = Game::instance();
		game.push(Game::GAME_WIN);
	}
}

/**
* @brief GameStateGame::Release
*/
void GameStateGame::touchBegin(const CShVector2 & pos)
{
	if (ShEntity2::Includes(m_pRestartButton, pos))
	{
		m_pPressedButton = m_pRestartButton;
	}
	else if (ShEntity2::Includes(m_pHomeButton, pos))
	{
		m_pPressedButton = m_pHomeButton;
	}
}

/**
* @brief GameStateGame::Release
*/
void GameStateGame::touchEnd(const CShVector2 & pos)
{
	if (shNULL != m_pPressedButton)
	{
		if (ShEntity2::Includes(m_pPressedButton, pos))
		{
			Game & game = Game::instance();

			if (m_pPressedButton == m_pRestartButton)
			{
				g_pInstance->Reset();
			}
			else if (m_pPressedButton == m_pHomeButton)
			{
				game.pop();
			}
		}

		m_pPressedButton = shNULL;
	}
}

/**
* @brief GameStateGame::Release
*/
void GameStateGame::touchMove(const CShVector2 & pos)
{
	// ...
}
