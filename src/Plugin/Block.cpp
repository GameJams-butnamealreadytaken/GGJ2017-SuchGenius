#include "Block.h"

/**
 * @brief Constructor
 */
Block::Block(void)
: m_pBody(shNULL)
, m_pSprite(shNULL)
{
	// ...
}

/**
 * @brief Destructor
 */
Block::~Block(void)
{
	// ...
}

/**
* @brief Initialize
*/
void Block::Initialize(b2Body * pBody, ShObject * pSprite, EBlockType type)
{
	m_pBody = pBody;
	m_type = type;
	m_pSprite = pSprite;
}

/**
* @brief Release
*/
void Block::Release(void)
{
	m_pBody = shNULL;
	m_pSprite = shNULL;
}

/**
* @brief GetType
*/
Block::EBlockType Block::GetType(void)
{
	return(m_type);
}

/**
* @brief GetBody
*/
b2Body * Block::GetBody(void)
{
	return(m_pBody);
}

/**
* @brief GetSprite
*/
ShObject * Block::GetSprite(void)
{
	return(m_pSprite);
}

