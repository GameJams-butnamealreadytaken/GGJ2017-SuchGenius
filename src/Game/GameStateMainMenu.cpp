#include "GameStateMainMenu.h"

/**
* @brief Game::Constructor
*/
GameStateMainMenu::GameStateMainMenu(void)
{
}

/**
* @brief Game::Destructor
*/
GameStateMainMenu::~GameStateMainMenu(void)
{
}

/**
* @brief Game::Initialize
*/
void GameStateMainMenu::init(void)
{
	//
	// Load level
	CShIdentifier levelIdentifier("ggj17_main_menu");
	bool loading = ShLevel::Load(levelIdentifier);
	SH_ASSERT(loading);


}

/**
* @brief Game::Release
*/
void GameStateMainMenu::release(void)
{

}

/**
* @brief Game::entered
*/
void GameStateMainMenu::entered(void)
{

}

/**
* @brief Game::exiting
*/
void GameStateMainMenu::exiting(void)
{

}

/**
* @brief Game::obscuring
*/
void GameStateMainMenu::obscuring(void)
{

}

/**
* @brief Game::obscuring
*/
void GameStateMainMenu::revealed(void)
{

}

/**
* @brief Game::Release
*/
void GameStateMainMenu::update(float dt)
{

}

/**
* @brief Game::Release
*/
void GameStateMainMenu::touchBegin(const CShVector2 & pos)
{
	// Generate wave
}

/**
* @brief Game::Release
*/
void GameStateMainMenu::touchEnd(const CShVector2 & pos)
{

}

/**
* @brief Game::Release
*/
void GameStateMainMenu::touchMove(const CShVector2 & pos)
{

}