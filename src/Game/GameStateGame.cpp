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
	int display_width = ShDisplay::GetWidth();
	int display_height = ShDisplay::GetHeight();

	float ratio_x = ORIGINAL_VIEWPORT_X / display_width;
	float ratio_y = ORIGINAL_VIEWPORT_Y / display_height;

	m_fRatio = shMax(ratio_x, ratio_y, 2.0f);

	m_pCamera = ShCamera::Create(GID(global), CShIdentifier("camera_game"), false);
	SH_ASSERT(shNULL != m_pCamera);

	ShCamera::SetPosition(m_pCamera, CShVector3(0.0f, 0.0f, 5.0f));
	ShCamera::SetTarget(m_pCamera, CShVector3(0.0f, 0.0f, 0.0f));
	ShCamera::SetUp(m_pCamera, CShVector3(0.0f, 1.0f, 0.0f));
	ShCamera::SetProjectionOrtho(m_pCamera);
	ShCamera::SetFarPlaneDistance(m_pCamera, 10.0f);
	ShCamera::SetNearPlaneDistance(m_pCamera, 0.1f);
	ShCamera::SetViewport(m_pCamera, display_width * m_fRatio, display_height * m_fRatio);
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
	ShCamera::SetCurrent2D(m_pCamera);
	ShCamera::SetCurrent3D(m_pCamera);

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
	ShCamera::SetCurrent2D(m_pCamera);
	ShCamera::SetCurrent3D(m_pCamera);

	unload();
	load();
}

/**
 * @brief GameStateGame::load
 */
void GameStateGame::load(void)
{
	CShString strLevelName;

	if (State::GetCurrentLevel() < 10)
	{
		strLevelName = CShString("level_0") + CShString::FromInt(State::GetCurrentLevel());
	}
	else
	{
		strLevelName = CShString("level_") + CShString::FromInt(State::GetCurrentLevel());
	}

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
void GameStateGame::touchBegin(const CShVector2 & pos_)
{
	CShVector2 pos = m_fRatio * pos_;

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
void GameStateGame::touchEnd(const CShVector2 & pos_)
{
	CShVector2 pos = m_fRatio * pos_;

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
void GameStateGame::touchMove(const CShVector2 & pos_)
{
	CShVector2 pos = m_fRatio * pos_;

	// ...
}
