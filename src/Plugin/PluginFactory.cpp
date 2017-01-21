#include "PluginFactory.h"

#include "ShSDK/ShSDK.h"

extern PluginGGJ2017 * g_pInstance = shNULL;

static void OnTouchDown(int iTouch, float positionX, float positionY)
{
	g_pInstance->OnTouchDown(iTouch, positionX, positionY);
}

static void OnTouchUp(int iTouch, float positionX, float positionY)
{
	g_pInstance->OnTouchUp(iTouch, positionX, positionY);
}

static void OnTouchMove(int iTouch, float positionX, float positionY)
{
	g_pInstance->OnTouchMove(iTouch, positionX, positionY);
}

extern "C"
{

PLUGIN_GGJ17_EXPORT void RegisterPluginGGJ2017(void)
{
	if (!g_pInstance)
	{
		g_pInstance = new PluginGGJ2017();

		ShInput::AddOnTouchDown(OnTouchDown);
		ShInput::AddOnTouchUp(OnTouchUp);
		ShInput::AddOnTouchMove(OnTouchMove);
	}

	ShApplication::RegisterPlugin(g_pInstance);
}

PLUGIN_GGJ17_EXPORT void UnRegisterPluginGGJ2017(void)
{
	ShInput::RemoveOnTouchDown(OnTouchDown);
	ShInput::RemoveOnTouchUp(OnTouchUp);
	ShInput::RemoveOnTouchMove(OnTouchMove);

	ShApplication::UnRegisterPlugin(g_pInstance);
}

}
