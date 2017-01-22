#include "GameStateWin.h"

#include "Game.h"

#define ANIM_INTRO_ENTERED_DURATION 0.5f
#define ANIM_INTRO_ENTERED_POPUP_LENGTH 400.0f
#define ANIM_INTRO_ENTERED_POPUP_BASE_Y 0.0f

/**
* @brief Constructor
*/
GameStateWin::GameStateWin(void)
: m_fStateTime(0.0f)
, m_pPressedButton(shNULL)
{
	// ...
}

/**
* @brief Destructor
*/
GameStateWin::~GameStateWin(void)
{
	// ...
}

/**
* @brief Initialize
*/
void GameStateWin::init(void)
{
	CShIdentifier levelIdentifier("level_win");
	bool loading = ShLevel::Load(levelIdentifier);
	SH_ASSERT(loading);

	int display_width = ShDisplay::GetWidth();
	int display_height = ShDisplay::GetHeight();

	float ratio_x = ORIGINAL_VIEWPORT_X / display_width;
	float ratio_y = ORIGINAL_VIEWPORT_Y / display_height;

	m_fRatio = shMax(ratio_x, ratio_y, 2.0f);

	m_pCamera = ShCamera::Create(levelIdentifier, CShIdentifier("camera_win"), false);
	SH_ASSERT(shNULL != m_pCamera);

	ShCamera::SetPosition(m_pCamera, CShVector3(0.0f, 0.0f, 5.0f));
	ShCamera::SetTarget(m_pCamera, CShVector3(0.0f, 0.0f, 0.0f));
	ShCamera::SetUp(m_pCamera, CShVector3(0.0f, 1.0f, 0.0f));
	ShCamera::SetProjectionOrtho(m_pCamera);
	ShCamera::SetFarPlaneDistance(m_pCamera, 10.0f);
	ShCamera::SetNearPlaneDistance(m_pCamera, 0.1f);
	ShCamera::SetViewport(m_pCamera, display_width * m_fRatio, display_height * m_fRatio);

	m_pButtonMenu = ShEntity2::Find(levelIdentifier, CShIdentifier("button_menu"));
	SH_ASSERT(shNULL != m_pButtonMenu);

	m_pButtonRetry = ShEntity2::Find(levelIdentifier, CShIdentifier("button_retry"));
	SH_ASSERT(shNULL != m_pButtonRetry);

	m_pButtonNext = ShEntity2::Find(levelIdentifier, CShIdentifier("button_next"));
	SH_ASSERT(shNULL != m_pButtonNext);

	m_pPopupBackgroundEntity = ShEntity2::Find(levelIdentifier, CShIdentifier("popup_background"));
	SH_ASSERT(shNULL != m_pPopupBackgroundEntity);
	ShEntity2::SetShow(m_pPopupBackgroundEntity, false);

	m_pPopupEntity = ShEntity2::Find(levelIdentifier, CShIdentifier("popup"));
	SH_ASSERT(shNULL != m_pPopupEntity);
	ShEntity2::SetShow(m_pPopupEntity, false);

	for (int i = 0; i < 3; ++i)
	{
		CShString strLevelName = CShString("sprite_ggj17_star_00") + CShString::FromInt(i + 1);
		m_aStarsEntities[i] = ShEntity2::Find(levelIdentifier, CShIdentifier(strLevelName));
		SH_ASSERT(shNULL != m_aStarsEntities[i]);
	}
}

/**
* @brief Release
*/
void GameStateWin::release(void)
{
	m_pPopupEntity = shNULL;

	ShLevel::Release();
}

/**
* @brief entered
*/
void GameStateWin::entered(void)
{
	m_eCurrentState = ANIM_INTRO_ENTERED;

	ShObject::SetRelativePositionY(m_pPopupEntity, ANIM_INTRO_ENTERED_POPUP_LENGTH);

	m_iClicCount = g_pInstance->GetLevelClicCount();

	ShEntity2::SetShow(m_pPopupEntity, true);
	ShEntity2::SetShow(m_pPopupBackgroundEntity, true);
	ShEntity2::SetAlpha(m_pPopupBackgroundEntity, 0.0f);

	m_fStateTime = 0.0f;

	for (int i = 0; i < 3; ++i)
	{
		ShEntity2::SetAlpha(m_aStarsEntities[i], 0.3f);
	}

	ShCamera::SetCurrent2D(m_pCamera);
	ShCamera::SetCurrent3D(m_pCamera);
}

/**
* @brief exiting
*/
void GameStateWin::exiting(void)
{
	m_pPressedButton = shNULL;
	ShEntity2::SetShow(m_pPopupEntity, false);
	ShEntity2::SetShow(m_pPopupBackgroundEntity, false);
}

/**
* @brief obscuring
*/
void GameStateWin::obscuring(void)
{
	m_pPressedButton = shNULL;
	ShEntity2::SetShow(m_pPopupEntity, false);
	ShEntity2::SetShow(m_pPopupBackgroundEntity, false);
}

/**
* @brief obscuring
*/
void GameStateWin::revealed(void)
{
	m_pPressedButton = shNULL;
	ShEntity2::SetShow(m_pPopupEntity, true);
	ShEntity2::SetShow(m_pPopupBackgroundEntity, true);
	ShEntity2::SetAlpha(m_pPopupBackgroundEntity, 0.0f);

	ShCamera::SetCurrent2D(m_pCamera);
	ShCamera::SetCurrent3D(m_pCamera);
}

/**
* @brief Release
*/
void GameStateWin::update(float dt)
{
	m_fStateTime += dt;

	switch (m_eCurrentState)
	{
		case ANIM_INTRO_ENTERED:
		{
			if (m_fStateTime > ANIM_INTRO_ENTERED_DURATION)
			{
				ShObject::SetRelativePositionY(m_pPopupEntity, ANIM_INTRO_ENTERED_POPUP_BASE_Y);

				int nbStarsWon = 1;

				int nbClickMin = g_nbMinPlay[GetCurrentLevel() - 1];
				if (m_iClicCount <= nbClickMin)
				{
					nbStarsWon = 3;
				}
				else if (m_iClicCount <= (nbClickMin + 2))
				{
					nbStarsWon = 2;
				}

				for (int i = 0; i < 3; ++i)
				{
					if (i < nbStarsWon)
					{
						ShEntity2::SetAlpha(m_aStarsEntities[i], 1.0f);
					}
				}

				g_pGameSave->SetLevelResult(GetCurrentLevel(), nbStarsWon);
				int nextLevel = GetCurrentLevel() + 1;
				g_pGameSave->SetLastLevelUnlocked(nextLevel);
				g_pGameSave->Save();
				m_eCurrentState = IDLE;
			}
			else
			{
				float progress = (m_fStateTime / ANIM_INTRO_ENTERED_DURATION);

				float progress_background = 2.0f * progress;
				float alpha = (progress_background < 0.6f) ? progress_background : 0.6f;
				ShEntity2::SetAlpha(m_pPopupBackgroundEntity, alpha);

				float progress_popup = BounceEase(progress);
				ShObject::SetRelativePositionY(m_pPopupEntity, (ANIM_INTRO_ENTERED_POPUP_BASE_Y + ANIM_INTRO_ENTERED_POPUP_LENGTH) - (ANIM_INTRO_ENTERED_POPUP_LENGTH * progress_popup));
			}
		}
		break;

		case IDLE:
		{
			// do nothing
		}
		break;
	}
}

/**
* @brief Release
*/
void GameStateWin::touchBegin(const CShVector2 & pos_)
{
	CShVector2 pos = m_fRatio * pos_;

	if (ShEntity2::Includes(m_pButtonMenu, pos))
	{
		m_pPressedButton = m_pButtonMenu;
	}
	else if (ShEntity2::Includes(m_pButtonRetry, pos))
	{
		m_pPressedButton = m_pButtonRetry;
	}
	else if (ShEntity2::Includes(m_pButtonNext, pos))
	{
		m_pPressedButton = m_pButtonNext;
	}
}

/**
* @brief Release
*/
void GameStateWin::touchEnd(const CShVector2 & pos_)
{
	CShVector2 pos = m_fRatio * pos_;

	if (shNULL != m_pPressedButton)
	{
		if (ShEntity2::Includes(m_pPressedButton, pos))
		{
			Game & game = Game::instance();

			if (m_pPressedButton == m_pButtonMenu)
			{
				game.pop();
				game.pop();
			}
			else if (m_pPressedButton == m_pButtonRetry)
			{
				game.pop();
			}
			else if (m_pPressedButton == m_pButtonNext)
			{
				int nextLevel = GetCurrentLevel() + 1;
				SetCurrentLevel(nextLevel);
				game.pop();
			}
		}
	}
}

/**
* @brief Release
*/
void GameStateWin::touchMove(const CShVector2 & pos_)
{
	CShVector2 pos = m_fRatio * pos_;

	// ...
}
