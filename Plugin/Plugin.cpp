#include "Plugin.h"
#include <iostream>

void APlugin::link(std::vector<APlugin *> *consummers)
{
	for (APlugin *plugin : *consummers)
		_consumers.push_back(plugin);
}

void APlugin::send()
{
	try
	{
		std::shared_ptr<AEvent> event = _createEvent(); // create the event
		std::vector<std::future<void>> futures;

		for (APlugin *plugin : _consumers)
		{
			futures.push_back(std::async(std::launch::async, &APlugin::receive, plugin, event)); // call all receive functions async
		}

		// Optionally wait for all async operations to complete
		for (auto &future : futures)
		{
			future.get();
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << "Exception in send: " << e.what() << std::endl;
	}
}
