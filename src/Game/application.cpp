#include "application.h"
#include "Game.h"
#include "inputs.h"

#include "../../src/Plugin/PluginFactory.h"

extern "C"
{

/**
 * @brief OnPreInitialize
 */
void OnPreInitialize(void)
{
	ShInput::AddOnTouchDown(OnTouchDown);
	ShInput::AddOnTouchUp(OnTouchUp);
	ShInput::AddOnTouchMove(OnTouchMove);
}

/**
 * @brief OnPostInitialize
 */
void OnPostInitialize(void)
{
	RegisterPluginGGJ2017();

	Game & game = Game::instance();
	game.initialize();
}

/**
 * @brief OnPreUpdate
 * @param dt
 */
void OnPreUpdate(float dt)
{
	Game & game = Game::instance();
	game.update(dt);
}

/**
 * @brief OnPostUpdate
 * @param dt
 */
void OnPostUpdate(float dt)
{
	SH_UNUSED(dt);
}

/**
 * @brief OnPreRelease
 */
void OnPreRelease(void)
{
	Game & game = Game::instance();
	game.release();

	UnRegisterPluginGGJ2017();
}

/**
 * @brief OnPostRelease
 */
void OnPostRelease(void)
{
	// ...
}

/**
 * @brief OnActivate
 */
void OnActivate(void)
{
	// ...
}

/**
 * @brief OnDeactivate
 * @param bAllowBackgroundUpdates
 * @param bAllowBackgroundInputs
 */
void OnDeactivate(bool & bAllowBackgroundUpdates, bool & bAllowBackgroundInputs)
{
	bAllowBackgroundUpdates = false;
	bAllowBackgroundInputs = false;
}

}
