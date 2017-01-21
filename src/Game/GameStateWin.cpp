#include "GameStateWin.h"

#include "Game.h"

/**
* @brief :Constructor
*/
GameStateWin::GameStateWin(void)
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
	// ...
}

/**
* @brief Release
*/
void GameStateWin::release(void)
{
	// ...
}

/**
* @brief entered
*/
void GameStateWin::entered(void)
{
	//
	// Load level
	CShIdentifier levelIdentifier("level_win");
	bool loading = ShLevel::Load(levelIdentifier);
	SH_ASSERT(loading);

	m_iClicCount = g_pInstance->GetLevelClicCount();
}

/**
* @brief exiting
*/
void GameStateWin::exiting(void)
{
	// ...
}

/**
* @brief obscuring
*/
void GameStateWin::obscuring(void)
{
	// ...
}

/**
* @brief obscuring
*/
void GameStateWin::revealed(void)
{
	// ...
}

/**
* @brief Release
*/
void GameStateWin::update(float dt)
{
	// ...
}

/**
* @brief Release
*/
void GameStateWin::touchBegin(const CShVector2 & pos)
{
	// ...
}

/**
* @brief Release
*/
void GameStateWin::touchEnd(const CShVector2 & pos)
{
	// ...
}

/**
* @brief Release
*/
void GameStateWin::touchMove(const CShVector2 & pos)
{
	// ...
}
