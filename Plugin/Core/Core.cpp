#include "Core.h"
#include <stdexcept>
#include <iostream>
#include <Plugin.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

Core::Core() {}

Core::~Core()
{
	for (auto it : _consumers)
	{
		for (APlugin *plugin : it.second)
			plugin->unregisterPlugin();
	}

	unloadPlugins();
}

void Core::loadPlugin(const std::string &path)
{
#ifdef _WIN32
	PluginHandle lib = LoadLibraryW(std::wstring(path.begin(), path.end()).c_str());
	if (lib == nullptr)
	{
		std::wcerr << L"Failed to load library: " << std::wstring(path.begin(), path.end()) << L" - Error code: " << GetLastError() << std::endl;
		throw std::runtime_error("Failed to load library");
		return;
	}
#else
	PluginHandle lib = dlopen(path.c_str(), RTLD_LAZY);
	if (!lib)
	{
		std::cout<<"*****************************"<<std::endl;
		std::cout<<path.c_str()<<std::endl;
		std::cerr << "Error: " << dlerror() << std::endl;
		throw std::runtime_error("Failed to load library");
		return;
	}
#endif
	_plugins.push_back(lib);

#ifdef _WIN32
	PluginDetails *details = (PluginDetails *)GetProcAddress(lib, "exports");
	if (details == nullptr)
	{
		std::wcerr << L"Failed to get plugin details: " << GetLastError() << std::endl;
		throw std::runtime_error("Failed to get plugin details");
		return;
	}
#else
	PluginDetails *details = (PluginDetails *)dlsym(lib, "exports");
	if (!details)
	{
		std::cerr << "Failed to get plugin details: " << dlerror() << std::endl;
		throw std::runtime_error("Failed to get plugin details");
		return;
	}
#endif
	// Add your code to handle the plugin details here
	if (details->apiVersion != PLUGIN_API_VERSION)
	{
		throw std::runtime_error("Plugin API version mismatch");
	}

	APlugin *plugin = details->initializeFunction();
	if (plugin == nullptr)
	{
		throw std::runtime_error("Failed to initialize plugin");
	}

	_consumers[details->pluginName].push_back(plugin);
}

void Core::unloadPlugins()
{
	for (auto handle : _plugins)
	{
#ifdef _WIN32
		FreeLibrary(handle);
#else
		dlclose(handle);
#endif
	}
	_plugins.clear();
}

const std::map<std::string, std::vector<APlugin *>> &Core::getConsumers() const
{
	return _consumers;
}