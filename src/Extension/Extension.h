#pragma once

#if defined(_WIN32)
#	if defined(Extension_EXPORTS)
#		define EXTENSION_EXPORT __declspec(dllexport)
#	else
#		define EXTENSION_EXPORT __declspec(dllimport)
#	endif // Extension_EXPORTS
#else // defined(_WIN32)
#	define EXTENSION_EXPORT
#endif

extern "C"
{
	EXTENSION_EXPORT void	ExtensionInitialize		(void);
	EXTENSION_EXPORT void	ExtensionRelease		(void);
}
