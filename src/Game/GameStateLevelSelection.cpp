#include "GameStateLevelSelection.h"

#include "Game.h"

#define ANIM_MAIN_MENU_DURATION 0.8f
#define ANIM_MAIN_MENU_LENGTH 720.0f

/**
* @brief GameStateLevelSelection::Constructor
*/
GameStateLevelSelection::GameStateLevelSelection(void)
: m_pPressedButton(shNULL)
, m_eCurrentState(IDLE)
, m_fStateTime(0.0f)
, m_iCurrentPageID(0)
, m_iLastPageID(0)
{
	// ...
}

/**
* @brief GameStateLevelSelection::Destructor
*/
GameStateLevelSelection::~GameStateLevelSelection(void)
{
	// ...
}

/**
* @brief GameStateLevelSelection::Initialize
*/
void GameStateLevelSelection::init(void)
{
	CShIdentifier levelIdentifier("level_selection");
	bool loading = ShLevel::Load(levelIdentifier);
	SH_ASSERT(loading);

	m_pCamera = ShCamera::Create(levelIdentifier, CShIdentifier("camera_selection"), false);
	SH_ASSERT(shNULL != m_pCamera);

	ShCamera::SetPosition(m_pCamera, CShVector3(0.0f, 0.0f, 5.0f));
	ShCamera::SetTarget(m_pCamera, CShVector3(0.0f, 0.0f, 0.0f));
	ShCamera::SetUp(m_pCamera, CShVector3(0.0f, 1.0f, 0.0f));
	ShCamera::SetProjectionOrtho(m_pCamera);
	ShCamera::SetFarPlaneDistance(m_pCamera, 10.0f);
	ShCamera::SetNearPlaneDistance(m_pCamera, 0.1f);
	ShCamera::SetViewport(m_pCamera, 1280.0f, 720.0f);

	m_pScreenObject = ShDummyAABB2::Find(levelIdentifier, CShIdentifier("zone_screen"));
	SH_ASSERT(shNULL != m_pScreenObject);
	ShEntity2::SetShow(m_pScreenObject, false);

	m_pButtonPrevious = ShEntity2::Find(levelIdentifier, CShIdentifier("button_previous"));
	SH_ASSERT(shNULL != m_pButtonPrevious);

	m_pButtonNext = ShEntity2::Find(levelIdentifier, CShIdentifier("button_next"));
	SH_ASSERT(shNULL != m_pButtonNext);

	m_pBackButton = ShEntity2::Find(levelIdentifier, CShIdentifier("button_return"));
	SH_ASSERT(shNULL != m_pBackButton);

	m_iCurrentPageID = 0;
	m_iLastPageID = 0;

	for (int i = 0; i < 9; ++i)
	{
		CShString strEntityName = CShString("sprite_ggj17_miniature_00") + CShString::FromInt(i+1);
		m_apThumbnails[i] = ShEntity2::Find(levelIdentifier, CShIdentifier(strEntityName));
		SH_ASSERT(shNULL != m_apThumbnails[i]);

		CShVector3 pos = ShObject::GetWorldPosition(m_apThumbnails[i]);
		++pos.m_z;
		pos.m_y -= 10.0f;
		pos.m_x -= 50.0f;

		for (int j = 0; j < 3; ++j)
		{
			if (j == 1)
			{
				pos.m_y += 30.0f;
			}

			m_apLevelSars[i][j] = ShEntity2::Create(levelIdentifier, GID(NULL), GID(layer_default), CShIdentifier("ggj17"), CShIdentifier("star"), pos, CShEulerAngles_ZERO, CShVector3(0.5f, 0.5f, 1.0f), false);
			SH_ASSERT(shNULL != m_apLevelSars[i][j]);
			ShEntity2::SetColor(m_apLevelSars[i][j], CShRGBAf(1.0, 0.0f, 0.0f, 1.0f));

			if (j == 1)
			{
				pos.m_y -= 30.0f;
			}
			pos.m_x += 50.0f;
		}
	}
}

/**
* @brief GameStateLevelSelection::Release
*/
void GameStateLevelSelection::release(void)
{
	m_pButtonNext = shNULL;
	m_pButtonPrevious = shNULL;

	m_pScreenObject = shNULL;

	for (int i = 0; i < 9; ++i)
	{
		m_apThumbnails[i] = shNULL;
	}


	ShLevel::Release();
}

/**
* @brief GameStateLevelSelection::entered
*/
void GameStateLevelSelection::entered(void)
{
	DisplayCurrentPage();

	ShCamera::SetCurrent2D(m_pCamera);
	ShCamera::SetCurrent3D(m_pCamera);

	ShEntity2::SetShow(m_pScreenObject, true);
}

/**
* @brief GameStateLevelSelection::exiting
*/
void GameStateLevelSelection::exiting(void)
{
	ShEntity2::SetShow(m_pScreenObject, false);
}

/**
* @brief GameStateLevelSelection::obscuring
*/
void GameStateLevelSelection::obscuring(void)
{
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			ShEntity2::SetShow(m_apLevelSars[i][j], false);
		}
	}

	ShEntity2::SetShow(m_pScreenObject, false);
}

/**
* @brief GameStateLevelSelection::revealed
*/
void GameStateLevelSelection::revealed(void)
{
	ShCamera::SetCurrent2D(m_pCamera);
	ShCamera::SetCurrent3D(m_pCamera);

	DisplayCurrentPage();

	ShEntity2::SetShow(m_pScreenObject, true);
}

/**
 * @brief GameStateLevelSelection::Release
 */
void GameStateLevelSelection::update(float dt)
{
	m_fStateTime += dt;

	switch (m_eCurrentState)
	{
		case ANIM_INTRO_ENTERED:
		{
			// ...
		}
		break;

		case IDLE:
		{
			// do nothing
		}
		break;

		case ANIM_OUTRO_MAIN_MENU:
		{
			if (m_fStateTime > ANIM_MAIN_MENU_DURATION)
			{
				ShObject::SetRelativePositionY(m_pScreenObject, -ANIM_MAIN_MENU_LENGTH);
				Game & game = Game::instance();
				game.pop();
			}
			else
			{
				float progress = BounceEase(m_fStateTime / ANIM_MAIN_MENU_DURATION);
				ShObject::SetRelativePositionY(m_pScreenObject, -ANIM_MAIN_MENU_LENGTH * progress);
			}
		}
		break;
	}
}

/**
 * @brief GameStateLevelSelection::prepareAnim
 * @param pParent
 */
void GameStateLevelSelection::prepareAnim(ShObject * pParent)
{
	ShObject::UnLink(m_pScreenObject, pParent);
	ShObject::Link(pParent, m_pScreenObject);

	ShObject::SetPositionY(m_pScreenObject, -ANIM_MAIN_MENU_LENGTH);

	ShEntity2::SetShow(m_pScreenObject, true);

	setState(ANIM_INTRO_ENTERED);
}

/**
 * @brief GameStateLevelSelection::Release
 */
void GameStateLevelSelection::touchBegin(const CShVector2 & pos)
{
	if (ShEntity2::Includes(m_pButtonPrevious, pos))
	{
		m_pPressedButton = m_pButtonPrevious;
	}
	else if (ShEntity2::Includes(m_pButtonNext, pos))
	{
		m_pPressedButton = m_pButtonNext;
	}
	else if (ShEntity2::Includes(m_pBackButton, pos))
	{
		m_pPressedButton = m_pBackButton;
	}
	else
	{
		int lasLevelUnlocked = g_pGameSave->GetLastLevelUnlocked();
		for (int i = 0; i < 9; ++i)
		{
			if ((i + (m_iCurrentPageID * 9) < lasLevelUnlocked))
			{
				if (ShEntity2::Includes(m_apThumbnails[i], pos))
				{
					m_pPressedButton = m_apThumbnails[i];
					break;
				}
			}
		}
	}
}

/**
 * @brief GameStateLevelSelection::Release
 */
void GameStateLevelSelection::touchEnd(const CShVector2 & pos)
{
	if (shNULL != m_pPressedButton)
	{
		if (ShEntity2::Includes(m_pPressedButton, pos))
		{
			Game & game = Game::instance();

			if (m_pPressedButton == m_pButtonPrevious)
			{
				if (0 != m_iCurrentPageID)
				{
					ShEntity2::SetAlpha(m_pButtonNext, 1.0f);
					m_iLastPageID = m_iCurrentPageID;
					--m_iCurrentPageID;
					DisplayCurrentPage();
				}
			}
			else if (m_pPressedButton == m_pButtonNext)
			{
				if (MAX_PAGE > m_iCurrentPageID)
				{
					ShEntity2::SetAlpha(m_pButtonPrevious, 1.0f);
					m_iLastPageID = m_iCurrentPageID;
					++m_iCurrentPageID;
					DisplayCurrentPage();
				}
			}
			else if (m_pPressedButton == m_pBackButton)
			{
				Game & game = Game::instance();
				((GameStateMainMenu*)game.get(Game::MAIN_MENU))->prepareAnim(m_pScreenObject);

				for (int i = 0; i < 9; ++i)
				{
					for (int j = 0; j < 3; ++j)
					{
						ShEntity2::SetShow(m_apLevelSars[i][j], false);
					}
				}

				setState(ANIM_OUTRO_MAIN_MENU);
			}
			else
			{
				for (int i = 0; i < 9; ++i)
				{
					if (ShEntity2::Includes(m_apThumbnails[i], pos))
					{
						// launch level i of page m_iCurrentPageID
						SetCurrentLevel(1 + ((m_iCurrentPageID * 9) + i));
						game.push(Game::GAME_LEVEL);
						break;
					}
				}
			}
		}

		m_pPressedButton = shNULL;
	}
}

/**
 * @brief GameStateLevelSelection::Release
 */
void GameStateLevelSelection::touchMove(const CShVector2 & pos)
{
	// ...
}

/**
 * @brief GameStateLevelSelection::setState
 * @param eState
 */
void GameStateLevelSelection::setState(EState eState)
{
	m_eCurrentState = eState;
	m_fStateTime = 0.0f;
}

/**
* @brief GameStateLevelSelection::DisplayCurrentPage
*/
void GameStateLevelSelection::DisplayCurrentPage(void)
{
	for (int i = 0; i < 9; ++i)
	{
		int levelResult = g_pGameSave->GetLevelResult((i + (9 * m_iCurrentPageID)) + 1);
		for (int j = 0; j < 3; ++j)
		{
			float alpha = 1.0f;
			if (j >= levelResult)
			{
				alpha = 0.2f;
			}

			ShEntity2::SetAlpha(m_apLevelSars[i][j], alpha);
			ShEntity2::SetShow(m_apLevelSars[i][j], true);
		}
	}

	if (0 == m_iCurrentPageID)
	{
		ShEntity2::SetAlpha(m_pButtonPrevious, 0.5f);
	}
	else if (MAX_PAGE == m_iCurrentPageID + 1)
	{
		ShEntity2::SetAlpha(m_pButtonNext, 0.5f);
	}
}
