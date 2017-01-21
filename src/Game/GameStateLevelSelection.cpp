#include "GameStateLevelSelection.h"

#include "Game.h"

/**
* @brief GameStateLevelSelection::Constructor
*/
GameStateLevelSelection::GameStateLevelSelection(void) : m_pPressedButton(shNULL), m_eCurrentState(IDLE), m_fStateTime(0.0f)
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

	for (int i = 0; i < 9; ++i)
	{
		CShString strEntityName = CShString("sprite_ggj17_miniature_00") + CShString::FromInt(i);
		m_apThumbnails[i] = ShEntity2::Find(levelIdentifier, CShIdentifier(strEntityName));
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
	// ...
}

/**
 * @brief GameStateLevelSelection::Release
 */
void GameStateLevelSelection::touchMove(const CShVector2 & pos)
{
	// ...
}
