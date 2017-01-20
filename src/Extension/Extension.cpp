#include "Extension.h"

#include "ShSDK/ShSDK.h"

typedef void (*register_fn)(void);
typedef void (*unregister_fn)(void);

register_fn pRegister = shNULL;
unregister_fn pUnRegister = shNULL;

const CShString strPluginFilePath("/mnt/workspace/Games/GGJ2017-SuchGenius/build/Debug/src/Plugin/libPlugin_Editor.so");
static CShDynamicLibrary plugin_library(strPluginFilePath);

extern "C"
{

EXTENSION_EXPORT void ExtensionInitialize(void)
{
	// ...
}

EXTENSION_EXPORT void ExtensionRelease(void)
{
	// ...
}

EXTENSION_EXPORT void ExtensionOnPluginStarted(const CShIdentifier & levelIdentifier)
{
	//
	// Load Library
	bool bInit = plugin_library.Initialize();

	//
	// Get Functions
	if (bInit)
	{
		pRegister = (register_fn)plugin_library.GetFunctionAddress(CShString("RegisterPluginGGJ2017"));
		SH_ASSERT(shNULL != pRegister);

		pUnRegister = (register_fn)plugin_library.GetFunctionAddress(CShString("UnRegisterPluginGGJ2017"));
		SH_ASSERT(shNULL != pUnRegister);
	}

	//
	// Call factory (auto-register)
	if (shNULL != pRegister)
	{
		pRegister();
	}
}

EXTENSION_EXPORT void ExtensionOnPluginStopped(const CShIdentifier & levelIdentifier)
{
	//
	// Call factory (auto-unregister)
	if (shNULL != pUnRegister)
	{
		pUnRegister();
	}

	//
	// Reset function pointers
	{
		pRegister = shNULL;
		pUnRegister = shNULL;
	}

	//
	// Unload Library
	plugin_library.Release();
}

}
