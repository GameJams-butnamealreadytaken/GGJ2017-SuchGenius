#include "State.h"

#include "Game.h"

int State::m_currentLevel = 1;

/**
 * @brief State::State
 */
State::State(void)
{
	// ...
}

/**
 * @brief State::~State
 */
State::~State(void)
{
	// ...
}

/**
* @brief State::GetCurrentLevel
*/
int State::GetCurrentLevel(void)
{
	return(m_currentLevel);
}

/**
* @brief State::SetCurrentLevel
*/
void State::SetCurrentLevel(int level)
{
	m_currentLevel = level;
}

/**
 * @brief State::touchBegin
 * @param pos
 */
void State::touchBegin(const CShVector2 & pos)
{
	// ...
}

/**
 * @brief State::touchEnd
 * @param pos
 */
void State::touchEnd(const CShVector2 & pos)
{
	// ...
}

/**
 * @brief State::touchMove
 * @param pos
 */
void State::touchMove(const CShVector2 & pos)
{
	// ...
}
