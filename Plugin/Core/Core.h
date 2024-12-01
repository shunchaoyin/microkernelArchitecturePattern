#pragma once


#include <map>
#include <string>
#include <vector>

//#include "Plugin.h"
class APlugin; // Forward declaration

class Core
{
public:
	Core();
	~Core();

	void loadPlugin(const std::string &path);
	 // Method to get consumers
    const std::map<std::string, std::vector<APlugin*>>& getConsumers() const;

private:
	void unloadPlugins();

#ifdef _WIN32
	using PluginHandle = HINSTANCE;
#else
	using PluginHandle = void *;
#endif

	std::vector<PluginHandle> _plugins;
	std::map<std::string, std::vector<APlugin *>> _consumers;
};