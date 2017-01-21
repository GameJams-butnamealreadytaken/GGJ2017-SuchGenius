#include "GameStateGame.h"

#include "Game.h"

/**
* @brief GameStateGame::Constructor
*/
GameStateGame::GameStateGame(void)
{
	// ...
}

/**
* @brief GameStateGame::Destructor
*/
GameStateGame::~GameStateGame(void)
{
	// ...
}

/**
* @brief GameStateGame::Initialize
*/
void GameStateGame::init(void)
{
	// ...
}

/**
* @brief GameStateGame::Release
*/
void GameStateGame::release(void)
{
	// ...
}

/**
* @brief GameStateGame::entered
*/
void GameStateGame::entered(void)
{
	//
	// Load level
	CShIdentifier levelIdentifier("level_000");
	bool loading = ShLevel::Load(levelIdentifier);
	SH_ASSERT(loading);
}

/**
* @brief GameStateGame::exiting
*/
void GameStateGame::exiting(void)
{
	// ...
}

/**
* @brief GameStateGame::obscuring
*/
void GameStateGame::obscuring(void)
{
	// ...
}

/**
* @brief GameStateGame::obscuring
*/
void GameStateGame::revealed(void)
{
	// ...
}

/**
* @brief GameStateGame::Release
*/
void GameStateGame::update(float dt)
{
	// ...
}

/**
* @brief GameStateGame::Release
*/
void GameStateGame::touchBegin(const CShVector2 & pos)
{
	// ...
}

/**
* @brief GameStateGame::Release
*/
void GameStateGame::touchEnd(const CShVector2 & pos)
{
	// ...
}

/**
* @brief GameStateGame::Release
*/
void GameStateGame::touchMove(const CShVector2 & pos)
{
	// ...
}
