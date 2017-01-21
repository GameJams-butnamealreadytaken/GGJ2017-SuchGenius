#include "PluginFactory.h"

#include "Plugin.h"

#include "ShSDK/ShSDK.h"

static PluginGGJ2017 * g_pInstance = shNULL;

extern "C"
{

void RegisterPluginGGJ2017(void)
{
	if (!g_pInstance)
	{
		g_pInstance = new PluginGGJ2017();
	}

	ShApplication::RegisterPlugin(g_pInstance);
}

void UnRegisterPluginGGJ2017(void)
{
	ShApplication::UnRegisterPlugin(g_pInstance);
}

}
