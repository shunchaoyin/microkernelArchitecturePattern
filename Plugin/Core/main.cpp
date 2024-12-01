// main.cpp
#include "Core.h"
#include <exception>
#include "Plugin.h"
#include <iostream>
#include <string>

int main()
{
    Core core;
    try
    {
        // Adjust the path as needed for your environment
#ifdef _WIN32
        core.loadPlugin("../lib/MyPlugin.dll");
#elif __APPLE__
        core.loadPlugin("../lib/libMyPlugin.dylib");
        core.loadPlugin("../lib/libHerPlugin.dylib");
#else
        core.loadPlugin("../lib/libMyPlugin.so");
#endif
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    auto &consumers = core.getConsumers();
    auto myPlugin = consumers.at("MyPlugin")[0];
    auto herPlugin_consumer = consumers.at("HerPlugin");
    myPlugin->link(&herPlugin_consumer);
    // For example, you can call send() on the plugin instances
    // Iterate over the loaded plugins and call send() on each instance
    // Assuming core is properly initialized with consumers
    for (const auto &[pluginName, plugins] : core.getConsumers())
    {
        std::cout << "Plugin Name: " << pluginName << "\n";
        for (const auto &plugin : plugins)
        {
            // Assuming Plugin has a method to display its information
            plugin->send();
        }
    }

    return 0;
}