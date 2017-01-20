#pragma once

#include "ShEngineExt/ShEngineExt.h"

class b2World;

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

private:

	b2World * m_pWorld;
};
