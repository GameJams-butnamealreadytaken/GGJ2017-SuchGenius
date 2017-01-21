#pragma once

#include "ShSDK/ShSDK.h"
#include "../Plugin/Plugin.h"

extern PluginGGJ2017 * g_pInstance;

inline float BounceEase(float t)
{
	if (t < (1.0f / 2.75f))
	{
		return (7.5625f * t * t);
	}
	else if (t < (2.0f / 2.75f))
	{
		t -= 1.5f / 2.75f;
		return (7.5625f * t * t + 0.75f);
	}
	else if (t < (2.5f / 2.75f))
	{
		t -= 2.25f / 2.75f;
		return (7.5625f * t * t + 0.9375f);
	}
	else
	{
		t -= 2.625f / 2.75f;
		return (7.5625f * t * t + 0.984375f);
	}

	SH_ASSERT_ALWAYS();
	return(0.0f);
}

class State
{

protected:

	State(void);
	virtual ~State(void);

public:

	virtual void init		(void) = 0;
	virtual void release	(void) = 0;

	virtual void entered	(void) = 0;
	virtual void exiting	(void) = 0;

	virtual void obscuring	(void) = 0;
	virtual void revealed	(void) = 0;

	virtual void update		(float dt) = 0;

	virtual void touchBegin	(const CShVector2 & pos);
	virtual void touchEnd	(const CShVector2 & pos);
	virtual void touchMove	(const CShVector2 & pos);

};
