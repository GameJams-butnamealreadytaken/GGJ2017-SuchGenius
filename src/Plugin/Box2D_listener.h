#pragma once

#include "ShSDK/ShSDK.h"
#include "ShEngineExt/ShEngineExt.h"

#include "Plugin.h"
#include "Box2D/Box2D.h"
#include "Block.h"

class PluginGGJ2017;

class Box2DListener : public b2ContactListener
{
public:

	//
	// Constructor / Destructor
						Box2DListener		(void);
	virtual				~Box2DListener		(void);

	void				Initialize			(PluginGGJ2017 * pPlugin);

	//
	//Contact
	virtual void		BeginContact(b2Contact* contact);
	virtual void		EndContact(b2Contact* contact);

private:

	PluginGGJ2017 * m_pPlugin;

};
