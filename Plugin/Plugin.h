#pragma once

#include <vector>
#include <future>
#include <memory>

#include "Event.h"

constexpr int PLUGIN_API_VERSION = 1;

#ifdef _WIN32
#ifdef BUILDING_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif
#else
#define DLL_EXPORT
#endif

class APlugin
{
public:
	DLL_EXPORT virtual ~APlugin() = default;

	DLL_EXPORT virtual void unregisterPlugin() = 0;

	void link(std::vector<APlugin *> *consumers); // interactive with other plugins
	void send();

protected:
	virtual std::shared_ptr<AEvent> _createEvent() = 0;
	virtual void receive(std::shared_ptr<AEvent> event) = 0;

private:
	std::vector<APlugin *> _consumers;
};

struct PluginDetails
{
	int apiVersion;
	const char *className;
	const char *pluginName;
	const char *pluginVersion;
	APlugin *(*initializeFunction)();
};

#define PLUGIN(classType, pluginName, pluginVersion) \
	extern "C"                                       \
	{                                                \
		DLL_EXPORT APlugin *getPlugin()              \
		{                                            \
			static classType plugin;                 \
			return &plugin;                          \
		}                                            \
                                                     \
		DLL_EXPORT PluginDetails exports =           \
			{                                        \
				PLUGIN_API_VERSION,                  \
				#classType,                          \
				pluginName,                          \
				pluginVersion,                       \
				getPlugin};                          \
	}