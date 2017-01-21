#include "GameStateLevelSelection.h"

#include "Game.h"

/**
* @brief GameStateLevelSelection::Constructor
*/
GameStateLevelSelection::GameStateLevelSelection(void) 
: m_pBackButton(shNULL)
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
	}

	for (int iPage = 0; iPage < MAX_PAGE; ++iPage)
	{
		for (int i = 0; i < 9; ++i)
		{
			CShString strEntityName = CShString("TODO") + CShString::FromInt(i);
			m_apLevelIcon[m_iCurrentPageID][i] = ShEntity2::Find(levelIdentifier, CShIdentifier(strEntityName));
		}
	}


	DisplayCurrentPage();
}

/**
* @brief GameStateLevelSelection::Release
*/
void GameStateLevelSelection::release(void)
{
	m_pButtonNext = shNULL;
	m_pButtonPrevious = shNULL;

	m_pScreenObject = shNULL;

	for (int iPage = 0; iPage < MAX_PAGE; ++iPage)
	{
		for (int i = 0; i < 9; ++i)
		{
			m_apLevelIcon[m_iCurrentPageID][i] = shNULL;
		}
	}

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
	ShEntity2::SetShow(m_pScreenObject, false);
}

/**
* @brief GameStateLevelSelection::revealed
*/
void GameStateLevelSelection::revealed(void)
{
	ShEntity2::SetShow(m_pScreenObject, true);
}

/**
 * @brief GameStateLevelSelection::Release
 */
void GameStateLevelSelection::update(float dt)
{
	// ...
}

/**
 * @brief GameStateLevelSelection::prepareAnim
 * @param pParent
 */
void GameStateLevelSelection::prepareAnim(ShObject * pParent)
{
	ShObject::Link(pParent, m_pScreenObject);

	ShObject::SetPositionY(m_pScreenObject, -720.0f);

	ShEntity2::SetShow(m_pScreenObject, true);
}

/**
 * @brief GameStateLevelSelection::Release
 */
void GameStateLevelSelection::touchBegin(const CShVector2 & pos)
{
	// ...
}

/**
 * @brief GameStateLevelSelection::Release
 */
void GameStateLevelSelection::touchEnd(const CShVector2 & pos)
{
	if (ShEntity2::Includes(m_pButtonPrevious, pos))
	{
		if (0 != m_iCurrentPageID)
		{
			ShEntity2::SetAlpha(m_pButtonNext, 1.0f);
			m_iLastPageID = m_iCurrentPageID;
			--m_iCurrentPageID;
			DisplayCurrentPage();
		}
	}
	else if (ShEntity2::Includes(m_pButtonNext, pos))
	{
		if (MAX_PAGE > m_iCurrentPageID)
		{
			ShEntity2::SetAlpha(m_pButtonPrevious, 1.0f);
			m_iLastPageID = m_iCurrentPageID;
			++m_iCurrentPageID;
			DisplayCurrentPage();
		}
	}
	else if (ShEntity2::Includes(m_pBackButton, pos))
	{
		Game & game = Game::instance();
		game.pop();
	}
	else
	{
		for (int i = 0; i < 9; ++i)
		{
			if (ShEntity2::Includes(m_apThumbnails[i], pos))
			{
				// launch level i of page m_iCurrentPageID
			}
		}
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
* @brief GameStateLevelSelection::DisplayCurrentPage
*/
void GameStateLevelSelection::DisplayCurrentPage(void)
{
	for (int i = 0; i < 9; ++i)
	{
		//ShEntity2::SetShow(m_apLevelIcon[m_iLastPageID][i], false);
		//ShEntity2::SetShow(m_apLevelIcon[m_iCurrentPageID][i], true);
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
