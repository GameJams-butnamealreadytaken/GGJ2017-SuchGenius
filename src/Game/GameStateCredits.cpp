#include "GameStateCredits.h"

#include "Game.h"

/**
* @brief Constructor
*/
GameStateCredits::GameStateCredits(void)
{
	// ...
}

/**
* @brief Destructor
*/
GameStateCredits::~GameStateCredits(void)
{
	// ...
}

/**
* @brief Initialize
*/
void GameStateCredits::init(void)
{
	// ...
}

/**
* @brief Release
*/
void GameStateCredits::release(void)
{
	// ...
}

/**
* @brief GameStateCredits::entered
*/
void GameStateCredits::entered(void)
{
	CShIdentifier levelIdentifier("level_credits");
	bool loading = ShLevel::Load(levelIdentifier);
	SH_ASSERT(loading);

	m_fTime = 0.0f;
}

/**
* @brief GameStateCredits::exiting
*/
void GameStateCredits::exiting(void)
{
	ShLevel::Release();
}

/**
* @brief GameStateCredits::obscuring
*/
void GameStateCredits::obscuring(void)
{
	// ...
}

/**
* @brief GameStateCredits::obscuring
*/
void GameStateCredits::revealed(void)
{
	// ...
}

/**
* @brief GameStateCredits::Release
*/
void GameStateCredits::update(float dt)
{
	m_fTime += dt;
}

/**
* @brief GameStateCredits::Release
*/
void GameStateCredits::touchBegin(const CShVector2 & pos)
{
	// ...
}

/**
* @brief GameStateCredits::Release
*/
void GameStateCredits::touchEnd(const CShVector2 & pos)
{
	if (m_fTime > 1.0f)
	{
		Game & game = Game::instance();
		game.pop();
	}
}

/**
* @brief GameStateCredits::Release
*/
void GameStateCredits::touchMove(const CShVector2 & pos)
{
	// ...
}
