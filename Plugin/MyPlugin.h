// MyPlugin.h
#pragma once

#include "Plugin.h"
#include <iostream>

class MyPlugin : public APlugin
{
public:
    DLL_EXPORT ~MyPlugin() override = default;

    DLL_EXPORT void unregisterPlugin() override
    {
        // Custom cleanup code
        std::cout << "MyPlugin unregistered" << std::endl;
    }

protected:
    std::shared_ptr<AEvent> _createEvent() override
    {
        // Create and return a new event
        return std::make_shared<SimpleEvent>("simpleEvent_MyPlugin", "MyPlugin_test data");
    } 

    void receive(std::shared_ptr<AEvent> event) override
    {
        // Handle the received event
        std::cout << "MyPlugin received an event" << std::endl;
        std::cout << "Event name: " << event->getType() << std::endl;
        std::cout << "Event data: " << event->getData() << std::endl;
    }
};

// Define the plugin details
PLUGIN(MyPlugin, "MyPlugin", "1.0")