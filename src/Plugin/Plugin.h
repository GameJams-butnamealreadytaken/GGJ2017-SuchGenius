#pragma once

#if defined(_WIN32)
#	if defined(Plugin_EXPORTS)
#		define PLUGIN_EXPORT __declspec(dllexport)
#	else
#		define PLUGIN_EXPORT __declspec(dllimport)
#	endif // Plugin_EXPORTS
#else // defined(_WIN32)
#	define PLUGIN_EXPORT
#endif

#include "ShSDK/ShSDK.h"
#include "ShEngineExt/ShEngineExt.h"

#include "Box2D/Box2D.h"

class PluginGGJ2017 : public CShPlugin
{
public:

	//
	// Constructor / Destructor
							PluginGGJ2017		(void);
	virtual					~PluginGGJ2017		(void);

	//
	// Play/Stop
	virtual	void			OnPlayStart			(const CShIdentifier & levelIdentifier) override;
	virtual	void			OnPlayStop			(const CShIdentifier & levelIdentifier) override;

	//
	// Update
	virtual	void			OnPreUpdate			(void) override;
	virtual	void			OnPostUpdate		(float dt) override;

	void					OnTouchDown			(int iTouch, float positionX, float positionY);
	void					OnTouchUp			(int iTouch, float positionX, float positionY);
	void					OnTouchMove			(int iTouch, float positionX, float positionY);

private:

	void					UpdateShineObjects	(void);

	void					DatasetParser		(ShObject * pObject, ShDataSet * pDataSet);
	b2Shape *				GenerateBlockShape	(ShObject * pObject, b2Body * pBody);

	static CShVector2		Convert_sh_b2		(b2Vec2 vec);
	static b2Vec2			Convert_sh_b2		(CShVector2 vec);

private:

	b2World *			m_pWorld;

	CShArray<b2Body *>	m_aBodyList;

	CShIdentifier m_levelIdentifier;

	struct ShockWave
	{
		ShEntity2 * pEntity;
		CShVector2 initialPosition;
		float time;
	};

	CShArray<ShockWave> m_aShockWave;
};
