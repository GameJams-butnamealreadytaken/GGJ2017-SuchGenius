#include "GameStateMainMenu.h"

#include "Game.h"

#define ANIM_LEVELS_DURATION 0.8f
#define ANIM_LEVELS_LENGTH 720.0f

/**
* @brief GameStateMainMenu::Constructor
*/
GameStateMainMenu::GameStateMainMenu(void) : m_pPressedButton(shNULL), m_eCurrentState(IDLE), m_fStateTime(0.0f)
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
	CShIdentifier levelIdentifier("main_menu");
	bool loading = ShLevel::Load(levelIdentifier);
	SH_ASSERT(loading);

	m_pScreenObject = ShDummyAABB2::Find(levelIdentifier, CShIdentifier("zone_screen"));
	SH_ASSERT(shNULL != m_pScreenObject);

	m_pButtonPlay = ShEntity2::Find(levelIdentifier, CShIdentifier("button_play"));
	SH_ASSERT(shNULL != m_pButtonPlay);

	m_pButtonSound = ShEntity2::Find(levelIdentifier, CShIdentifier("button_sound"));
	SH_ASSERT(shNULL != m_pButtonSound);

	m_pButtonLevels = ShEntity2::Find(levelIdentifier, CShIdentifier("button_levels"));
	SH_ASSERT(shNULL != m_pButtonLevels);

	m_pButtonInfo = ShEntity2::Find(levelIdentifier, CShIdentifier("button_info"));
	SH_ASSERT(shNULL != m_pButtonInfo);

	m_pIconSoundOn = ShEntity2::Find(levelIdentifier, CShIdentifier("icon_sound_on"));
	SH_ASSERT(shNULL != m_pIconSoundOn);

	m_pIconSoundOff = ShEntity2::Find(levelIdentifier, CShIdentifier("icon_sound_off"));
	SH_ASSERT(shNULL != m_pIconSoundOff);
}

/**
* @brief GameStateMainMenu::Release
*/
void GameStateMainMenu::release(void)
{
	m_pButtonSound = shNULL;
	m_pButtonLevels = shNULL;
	m_pButtonInfo = shNULL;

	m_pButtonPlay = shNULL;

	m_pScreenObject = shNULL;

	ShLevel::Release();
}

/**
* @brief GameStateMainMenu::entered
*/
void GameStateMainMenu::entered(void)
{
	setState(IDLE); // FIXME : INTRO

	ShEntity2::SetShow(m_pScreenObject, true);
}

/**
* @brief GameStateMainMenu::exiting
*/
void GameStateMainMenu::exiting(void)
{
	ShEntity2::SetShow(m_pScreenObject, false);
}

/**
* @brief GameStateMainMenu::obscuring
*/
void GameStateMainMenu::obscuring(void)
{
	ShEntity2::SetShow(m_pScreenObject, false);
}

/**
* @brief GameStateMainMenu::revealed
*/
void GameStateMainMenu::revealed(void)
{
	ShEntity2::SetShow(m_pScreenObject, true);
}

/**
 * @brief GameStateMainMenu::Release
 */
void GameStateMainMenu::update(float dt)
{
	m_fStateTime += dt;

	switch (m_eCurrentState)
	{
		case IDLE:
		{
			// do nothing
		}
		break;

		case ANIM_OUTRO_LEVELS:
		{
			if (m_fStateTime > ANIM_LEVELS_DURATION)
			{
				ShObject::SetPositionY(m_pScreenObject, ANIM_LEVELS_LENGTH);
				Game & game = Game::instance();
				game.push(Game::LEVEL_SELECTION);
			}
			else
			{
				float progress = (m_fStateTime / ANIM_LEVELS_DURATION);
				ShObject::SetPositionY(m_pScreenObject, ANIM_LEVELS_LENGTH * progress * progress);
			}
		}
		break;

		default:
		{
			// ...
		}
		break;
	}
}

/**
 * @brief Unload level
 * @return
 */
void GameStateMainMenu::setState(GameStateMainMenu::EState eState)
{
	m_eCurrentState = eState;
	m_fStateTime = 0.0f;
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
	else if (ShEntity2::Includes(m_pButtonSound, pos))
	{
		m_pPressedButton = m_pButtonSound;
	}
	else if (ShEntity2::Includes(m_pButtonLevels, pos))
	{
		m_pPressedButton = m_pButtonLevels;
	}
	else if (ShEntity2::Includes(m_pButtonInfo, pos))
	{
		m_pPressedButton = m_pButtonInfo;
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
			Game & game = Game::instance();

			if (m_pPressedButton == m_pButtonPlay)
			{
				game.push(Game::GAME_LEVEL);
			}
			else if (m_pPressedButton == m_pButtonSound)
			{
				bool bMuted = game.toggleMute();
				ShEntity2::SetShow(m_pIconSoundOn, !bMuted);
				ShEntity2::SetShow(m_pIconSoundOff, bMuted);
			}
			else if (m_pPressedButton == m_pButtonLevels)
			{
				setState(ANIM_OUTRO_LEVELS);
				((GameStateLevelSelection*)game.get(Game::LEVEL_SELECTION))->prepareAnim(m_pScreenObject);
			}
			else if (m_pPressedButton == m_pButtonInfo)
			{

			}
			else
			{
				SH_ASSERT_ALWAYS();
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
