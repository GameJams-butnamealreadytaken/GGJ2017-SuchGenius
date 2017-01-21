#include "PluginFactory.h"

#include "Plugin.h"

#include "ShSDK/ShSDK.h"

static PluginGGJ2017 instance;

extern "C"
{

void RegisterPluginGGJ2017(void)
{
	ShApplication::RegisterPlugin(&instance);
}

void UnRegisterPluginGGJ2017(void)
{
	ShApplication::UnRegisterPlugin(&instance);
}

}
