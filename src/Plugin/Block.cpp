#include "Block.h"

/**
 * @brief Constructor
 */
Block::Block(void)
: m_pBody(shNULL)
, m_pSprite(shNULL)
, m_cptCollision(0)
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

/**
* @brief GetCptCollision
*/
int Block::GetCptCollision(void)
{
	return(m_cptCollision);
}

/**
* @brief SetCptCollision
* @param inc
*/
void Block::SetCptCollision(bool inc)
{
	if (inc)
	{
		++m_cptCollision;
	}
	else
	{
		--m_cptCollision;
	}
}

