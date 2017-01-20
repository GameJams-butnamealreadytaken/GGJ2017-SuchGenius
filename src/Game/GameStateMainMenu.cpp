#include "GameStateMainMenu.h"

/**
* @brief GameStateMainMenu::Constructor
*/
GameStateMainMenu::GameStateMainMenu(void)
: pButtonPlay(shNULL)
{
}

/**
* @brief GameStateMainMenu::Destructor
*/
GameStateMainMenu::~GameStateMainMenu(void)
{
}

/**
* @brief GameStateMainMenu::Initialize
*/
void GameStateMainMenu::init(void)
{
}

/**
* @brief GameStateMainMenu::Release
*/
void GameStateMainMenu::release(void)
{
}

/**
* @brief GameStateMainMenu::entered
*/
void GameStateMainMenu::entered(void)
{
	//
	// Load level
	CShIdentifier levelIdentifier("main_menu");
	bool loading = ShLevel::Load(levelIdentifier);
	SH_ASSERT(loading);

	pButtonPlay = ShEntity2::Find(levelIdentifier, CShIdentifier("sprite_ggj17_main_menu_button_play_001"));
	SH_ASSERT(shNULL != pButtonPlay);
}

/**
* @brief GameStateMainMenu::exiting
*/
void GameStateMainMenu::exiting(void)
{
	pButtonPlay = shNULL;
}

/**
* @brief GameStateMainMenu::obscuring
*/
void GameStateMainMenu::obscuring(void)
{

}

/**
* @brief GameStateMainMenu::obscuring
*/
void GameStateMainMenu::revealed(void)
{

}

/**
* @brief GameStateMainMenu::Release
*/
void GameStateMainMenu::update(float dt)
{

}

/**
* @brief GameStateMainMenu::Release
*/
void GameStateMainMenu::touchBegin(const CShVector2 & pos)
{
	// Generate wave
	if (ShEntity2::Includes(pButtonPlay, pos))
	{
		Game::instance().pop();
		Game::instance().push(Game::GAME_LEVEL);
	}
}

/**
* @brief GameStateMainMenu::Release
*/
void GameStateMainMenu::touchEnd(const CShVector2 & pos)
{

}

/**
* @brief GameStateMainMenu::Release
*/
void GameStateMainMenu::touchMove(const CShVector2 & pos)
{

}