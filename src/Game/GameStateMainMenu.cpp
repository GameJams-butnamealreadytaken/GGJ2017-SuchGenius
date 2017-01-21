#include "GameStateMainMenu.h"

#include "Game.h"

/**
* @brief GameStateMainMenu::Constructor
*/
GameStateMainMenu::GameStateMainMenu(void) : m_pPressedButton(shNULL), m_pButtonPlay(shNULL)
{
	// ...
}

/**
* @brief GameStateMainMenu::Destructor
*/
GameStateMainMenu::~GameStateMainMenu(void)
{
	// ...
}

/**
* @brief GameStateMainMenu::Initialize
*/
void GameStateMainMenu::init(void)
{
	// ...
}

/**
* @brief GameStateMainMenu::Release
*/
void GameStateMainMenu::release(void)
{
	// ...
}

/**
* @brief GameStateMainMenu::entered
*/
void GameStateMainMenu::entered(void)
{
	load();
}

/**
* @brief GameStateMainMenu::exiting
*/
void GameStateMainMenu::exiting(void)
{
	unload();
}

/**
* @brief GameStateMainMenu::obscuring
*/
void GameStateMainMenu::obscuring(void)
{
	unload();
}

/**
* @brief GameStateMainMenu::obscuring
*/
void GameStateMainMenu::revealed(void)
{
	load();
}

/**
 * @brief Load level
 * @return
 */
bool GameStateMainMenu::load(void)
{
	CShIdentifier levelIdentifier("main_menu");
	bool loading = ShLevel::Load(levelIdentifier);
	SH_ASSERT(loading);

	m_pButtonPlay = ShEntity2::Find(levelIdentifier, CShIdentifier("sprite_ggj17_main_menu_button_play_001"));
	SH_ASSERT(shNULL != m_pButtonPlay);
}

/**
 * @brief Unload level
 * @return
 */
bool GameStateMainMenu::unload(void)
{
	m_pButtonPlay = shNULL;

	ShLevel::Release();
}


/**
 * @brief GameStateMainMenu::Release
 */
void GameStateMainMenu::update(float dt)
{
	// ...
}

/**
 * @brief GameStateMainMenu::Release
 */
void GameStateMainMenu::touchBegin(const CShVector2 & pos)
{
	if (ShEntity2::Includes(m_pButtonPlay, pos))
	{
		m_pPressedButton = m_pButtonPlay;
	}
}

/**
 * @brief GameStateMainMenu::Release
 */
void GameStateMainMenu::touchEnd(const CShVector2 & pos)
{
	if (shNULL != m_pPressedButton)
	{
		if (ShEntity2::Includes(m_pPressedButton, pos))
		{
			if (m_pPressedButton == m_pButtonPlay)
			{
				Game::instance().push(Game::GAME_LEVEL);
			}
		}

		m_pPressedButton = shNULL;
	}
}

/**
 * @brief GameStateMainMenu::Release
 */
void GameStateMainMenu::touchMove(const CShVector2 & pos)
{
	// ...
}
