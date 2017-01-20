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
	//
	// Load level
	CShIdentifier levelIdentifier("ggj17_menu_main");
	bool loading = ShLevel::Load(levelIdentifier);
	SH_ASSERT(loading);

	ShEntity2::Find(levelIdentifier, CShIdentifier("sprite_ggj17_main_menu_button_play_001"));
	SH_ASSERT(shNULL != pButtonPlay);
}

/**
* @brief GameStateMainMenu::Release
*/
void GameStateMainMenu::release(void)
{
	pButtonPlay = shNULL;
}

/**
* @brief GameStateMainMenu::entered
*/
void GameStateMainMenu::entered(void)
{

}

/**
* @brief GameStateMainMenu::exiting
*/
void GameStateMainMenu::exiting(void)
{

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
		// launch the game
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