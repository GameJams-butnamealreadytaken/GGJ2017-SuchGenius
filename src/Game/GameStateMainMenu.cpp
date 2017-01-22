#include "GameStateMainMenu.h"

#include "Game.h"

#define ANIM_LEVELS_DURATION 0.8f
#define ANIM_LEVELS_LENGTH 720.0f

#define ANIM_INTRO_ENTERED_DURATION 0.4f
#define ANIM_INTRO_ENTERED_TITLE_LENGTH 120.0f
#define ANIM_INTRO_ENTERED_TITLE_BASE_Y 240.0f
#define ANIM_INTRO_ENTERED_PLAY_LENGTH 480.0f
#define ANIM_INTRO_ENTERED_PLAY_BASE_Y 0.0f
#define ANIM_INTRO_ENTERED_BUTTONS_LENGTH 480.0f
#define ANIM_INTRO_ENTERED_BUTTONS_BASE_Y -250.0f
/**
 * @brief Constructor
 */
GameStateMainMenu::GameStateMainMenu(void) : m_pPressedButton(shNULL), m_eCurrentState(IDLE), m_fStateTime(0.0f)
{
	// ...
}

/**
 * @brief Destructor
 */
GameStateMainMenu::~GameStateMainMenu(void)
{
	// ...
}

/**
 * @brief Initialize
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

	m_pTitleEntity = ShEntity2::Find(levelIdentifier, CShIdentifier("title"));
	SH_ASSERT(shNULL != m_pTitleEntity);

	setState(ANIM_INTRO_ENTERED);
}

/**
 * @brief Release
 */
void GameStateMainMenu::release(void)
{
	m_pTitleEntity = shNULL;

	m_pIconSoundOn = shNULL;
	m_pIconSoundOff = shNULL;

	m_pButtonSound = shNULL;
	m_pButtonLevels = shNULL;
	m_pButtonInfo = shNULL;

	m_pButtonPlay = shNULL;

	m_pScreenObject = shNULL;

	ShLevel::Release();
}

/**
 * @brief entered
 */
void GameStateMainMenu::entered(void)
{
	ShEntity2::SetShow(m_pScreenObject, true);
}

/**
 * @brief exiting
 */
void GameStateMainMenu::exiting(void)
{
	ShEntity2::SetShow(m_pScreenObject, false);
}

/**
 * @brief obscuring
 */
void GameStateMainMenu::obscuring(void)
{
	ShEntity2::SetShow(m_pScreenObject, false);
}

/**
 * @brief revealed
 */
void GameStateMainMenu::revealed(void)
{
	ShEntity2::SetShow(m_pScreenObject, true);
}

/**
 * @brief update
 */
void GameStateMainMenu::update(float dt)
{
	m_fStateTime += dt;

	switch (m_eCurrentState)
	{
		case ANIM_INTRO_ENTERED:
		{
			//
			//
			if (m_fStateTime > ANIM_INTRO_ENTERED_DURATION)
			{
				ShObject::SetRelativePositionY(m_pTitleEntity, ANIM_INTRO_ENTERED_TITLE_BASE_Y);
			}
			else
			{
				float progress = (m_fStateTime / ANIM_INTRO_ENTERED_DURATION);
				ShObject::SetRelativePositionY(m_pTitleEntity, (ANIM_INTRO_ENTERED_TITLE_BASE_Y + ANIM_INTRO_ENTERED_PLAY_LENGTH) - (ANIM_INTRO_ENTERED_PLAY_LENGTH * progress));
			}

			//
			// Play
			if ((m_fStateTime - 0.1f) > ANIM_INTRO_ENTERED_DURATION)
			{
				ShObject::SetRelativePositionY(m_pButtonPlay, ANIM_INTRO_ENTERED_PLAY_BASE_Y);
			}
			else
			{
				float progress = ((m_fStateTime - 0.1f) / ANIM_INTRO_ENTERED_DURATION);
				ShObject::SetRelativePositionY(m_pButtonPlay, (ANIM_INTRO_ENTERED_PLAY_BASE_Y - ANIM_INTRO_ENTERED_PLAY_LENGTH) + (ANIM_INTRO_ENTERED_PLAY_LENGTH * progress));
			}

			//
			// Sound
			if ((m_fStateTime - 0.2f) > ANIM_INTRO_ENTERED_DURATION)
			{
				ShObject::SetRelativePositionY(m_pButtonSound, ANIM_INTRO_ENTERED_BUTTONS_BASE_Y);
			}
			else
			{
				float progress = ((m_fStateTime - 0.2f) / ANIM_INTRO_ENTERED_DURATION);
				ShObject::SetRelativePositionY(m_pButtonSound, (ANIM_INTRO_ENTERED_BUTTONS_BASE_Y - ANIM_INTRO_ENTERED_BUTTONS_LENGTH) + (ANIM_INTRO_ENTERED_BUTTONS_LENGTH * progress));
			}

			//
			// Levels
			if ((m_fStateTime - 0.3f) > ANIM_INTRO_ENTERED_DURATION)
			{
				ShObject::SetRelativePositionY(m_pButtonLevels, ANIM_INTRO_ENTERED_BUTTONS_BASE_Y);
			}
			else
			{
				float progress = ((m_fStateTime - 0.3f) / ANIM_INTRO_ENTERED_DURATION);
				ShObject::SetRelativePositionY(m_pButtonLevels, (ANIM_INTRO_ENTERED_BUTTONS_BASE_Y - ANIM_INTRO_ENTERED_BUTTONS_LENGTH) + (ANIM_INTRO_ENTERED_BUTTONS_LENGTH * progress));
			}


			//
			// Info
			if ((m_fStateTime - 0.4f) > ANIM_INTRO_ENTERED_DURATION)
			{
				ShObject::SetRelativePositionY(m_pButtonInfo, ANIM_INTRO_ENTERED_BUTTONS_BASE_Y);
			}
			else
			{
				float progress = ((m_fStateTime - 0.4f) / ANIM_INTRO_ENTERED_DURATION);
				ShObject::SetRelativePositionY(m_pButtonInfo, (ANIM_INTRO_ENTERED_BUTTONS_BASE_Y - ANIM_INTRO_ENTERED_BUTTONS_LENGTH) + (ANIM_INTRO_ENTERED_BUTTONS_LENGTH * progress));
			}

			//
			// change state
			if ((m_fStateTime - 0.5f) > ANIM_INTRO_ENTERED_DURATION)
			{
				setState(IDLE);
			}
		}
		break;

		case IDLE:
		{
			if (g_pInputs->IsPressEnter())
			{
				SetCurrentLevel(g_pGameSave->GetLastLevelUnlocked());
				Game & game = Game::instance();
				game.push(Game::GAME_LEVEL);
			}
		}
		break;

		case ANIM_OUTRO_LEVELS:
		{
			if (m_fStateTime > ANIM_LEVELS_DURATION)
			{
				ShObject::SetRelativePositionY(m_pScreenObject, ANIM_LEVELS_LENGTH);
				Game & game = Game::instance();
				game.push(Game::LEVEL_SELECTION);
			}
			else
			{
				float progress = BounceEase(m_fStateTime / ANIM_LEVELS_DURATION);
				ShObject::SetRelativePositionY(m_pScreenObject, ANIM_LEVELS_LENGTH * progress);
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

	switch (m_eCurrentState)
	{
		case ANIM_INTRO_ENTERED:
		{
			CShVector2 pos = ShObject::GetWorldPosition2(m_pScreenObject);

			ShEntity2::SetRelativePositionY(m_pButtonPlay, pos.m_y - ANIM_INTRO_ENTERED_PLAY_LENGTH);

			ShEntity2::SetRelativePositionY(m_pButtonSound, pos.m_y - ANIM_INTRO_ENTERED_BUTTONS_LENGTH);
			ShEntity2::SetRelativePositionY(m_pButtonLevels, pos.m_y - ANIM_INTRO_ENTERED_BUTTONS_LENGTH);
			ShEntity2::SetRelativePositionY(m_pButtonInfo, pos.m_y - ANIM_INTRO_ENTERED_BUTTONS_LENGTH);
		}
		break;

		case IDLE:
		{
			// ...
		}
		break;

		case ANIM_OUTRO_LEVELS:
		{
			// ...
		}
		break;

		default:
		{
			SH_ASSERT_ALWAYS();
		}
		break;
	}
}

/**
 * @brief GameStateMainMenu::prepareAnim
 * @param pParent
 */
void GameStateMainMenu::prepareAnim(ShObject * pParent)
{
	ShObject::UnLink(m_pScreenObject, pParent);
	ShObject::Link(pParent, m_pScreenObject);

	ShObject::SetPositionY(m_pScreenObject, ANIM_LEVELS_LENGTH);

	ShEntity2::SetShow(m_pScreenObject, true);

	setState(IDLE);
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
				SetCurrentLevel(g_pGameSave->GetLastLevelUnlocked());
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
				game.push(Game::CREDITS);
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
