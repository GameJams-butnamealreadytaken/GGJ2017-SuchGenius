#include "Box2D_listener.h"

/**
 * @brief Constructor
 */
Box2DListener::Box2DListener(void)
{
	// ...
}

/**
 * @brief Destructor
 */
Box2DListener::~Box2DListener(void)
{
	// ...
}

void Box2DListener::Initialize(PluginGGJ2017 * pPlugin)
{
	m_pPlugin = pPlugin;
}

/**
* @brief BeginContact
*/
void Box2DListener::BeginContact(b2Contact * contact)
{
	Block * pBlockA = static_cast<Block *>(contact->GetFixtureA()->GetBody()->GetUserData());
	Block * pBlockB = static_cast<Block *>(contact->GetFixtureB()->GetBody()->GetUserData());

	if (Block::SENSOR == pBlockA->GetType() && Block::PLAYER == pBlockB->GetType())
	{
		m_pPlugin->SetPlayerOnArrival(true);
	}
	else if (Block::SENSOR == pBlockB->GetType() && Block::PLAYER == pBlockA->GetType())
	{
		m_pPlugin->SetPlayerOnArrival(true);
	}
}

/**
* @brief EndContact
*/
void Box2DListener::EndContact(b2Contact * contact)
{
	Block * pBlockA = static_cast<Block *>(contact->GetFixtureA()->GetBody()->GetUserData());
	Block * pBlockB = static_cast<Block *>(contact->GetFixtureB()->GetBody()->GetUserData());

	if (Block::SENSOR == pBlockA->GetType() && Block::PLAYER == pBlockB->GetType())
	{
		m_pPlugin->SetPlayerOnArrival(false);
	}
	else if (Block::SENSOR == pBlockB->GetType() && Block::PLAYER == pBlockA->GetType())
	{
		m_pPlugin->SetPlayerOnArrival(false);
	}
}

