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
	m_pCamera = ShCamera::Create(GID(global), CShIdentifier("camera_credits"), false);
	SH_ASSERT(shNULL != m_pCamera);

	ShCamera::SetPosition(m_pCamera, CShVector3(0.0f, 0.0f, 5.0f));
	ShCamera::SetTarget(m_pCamera, CShVector3(0.0f, 0.0f, 0.0f));
	ShCamera::SetUp(m_pCamera, CShVector3(0.0f, 1.0f, 0.0f));
	ShCamera::SetProjectionOrtho(m_pCamera);
	ShCamera::SetFarPlaneDistance(m_pCamera, 10.0f);
	ShCamera::SetNearPlaneDistance(m_pCamera, 0.1f);
	ShCamera::SetViewport(m_pCamera, 1280.0f, 720.0f);
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

	ShCamera::SetCurrent2D(m_pCamera);
	ShCamera::SetCurrent3D(m_pCamera);

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
	ShCamera::SetCurrent2D(m_pCamera);
	ShCamera::SetCurrent3D(m_pCamera);
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
