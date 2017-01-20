#pragma once

#include "ShEngineExt/ShEngineExt.h"

class PluginGGJ2017 : public CShPlugin
{
public:

	//
	// Constructor / Destructor
							PluginGGJ2017		(void);
	virtual					~PluginGGJ2017		(void);

	virtual	void			OnPlayStart			(const CShIdentifier & levelIdentifier) override;
	virtual	void			OnPlayStop			(const CShIdentifier & levelIdentifier) override;
};
