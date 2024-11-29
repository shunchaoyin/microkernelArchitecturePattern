#include "Core.h"
#include <stdexcept>
#include <windows.h>

Core::Core()
{
}

Core::~Core()
{
	for (auto it : _consumers)
	{
		for (APlugin* plugin : it.second)
			plugin->unregisterPlugin();
	}

	unloadPlugins();
}

void Core::loadPlugin(std::string path)
{
	HINSTANCE lib;
	lib = LoadLibraryW(std::wstring(path.begin(), path.end()).c_str());
	if (lib == nullptr)
	{
		throw std::runtime_error("Failed to load library");
		return;
	}
	_plugins.push_back(lib);

	PluginDetails* details = (PluginDetails*)GetProcAddress(lib, "exports");
	if (details == nullptr)
	{
		throw std::runtime_error("Failed to get plugin details");
		return;
	}

	if (details->apiVersion < PLUGIN_API_VERSION)
	{
		throw std::runtime_error("Incompatible plugin API version");
		return;
	}

	APlugin* plugin = details->initializeFunction();
}

void Core::unloadPlugins()
{
	for (HINSTANCE lib : _plugins)
	{
		bool freeResult = FreeLibrary(lib);
		if (!freeResult)
		{
			throw std::runtime_error("Failed to free library");
		}
	}
}
