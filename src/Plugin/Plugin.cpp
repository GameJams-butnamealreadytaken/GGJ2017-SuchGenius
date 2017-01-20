#include "Plugin.h"

#include "ShSDK/ShSDK.h"

#include "Box2D/Box2D.h"

const CShIdentifier plugin_identifier("PluginGGJ2017");
const b2Vec2 gravity(0.0f, -9.8f);

/**
 * @brief Constructor
 */
PluginGGJ2017::PluginGGJ2017(void) : CShPlugin(plugin_identifier)
{
	// ...
}

/**
 * @brief Destructor
 */
PluginGGJ2017::~PluginGGJ2017(void)
{
	// ...
}

/**
 * @brief OnPlayStart
 * @param levelIdentifier
 */
void PluginGGJ2017::OnPlayStart(const CShIdentifier & levelIdentifier)
{
	m_pWorld = new b2World(gravity);
}

/**
 * @brief OnPlayStop
 * @param levelIdentifier
 */
void PluginGGJ2017::OnPlayStop(const CShIdentifier & levelIdentifier)
{
	SH_SAFE_DELETE(m_pWorld);
}

/**
 * @brief OnPreUpdate
 */
void PluginGGJ2017::OnPreUpdate(void)
{
	// ...
}

/**
 * @brief OnPostUpdate
 * @param dt
 */
void PluginGGJ2017::OnPostUpdate(float dt)
{
	m_pWorld->Step(dt, 8, 3);
}
