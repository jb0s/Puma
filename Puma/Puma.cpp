#include "Puma.h"

namespace Puma
{
	void start(std::string service)
	{
#ifdef DEVELOPMENT_MODE
		std::cout << "Welcome to Puma " << service << ". This build is for testing purposes. Compiled on " << __DATE__ << ".\n";
		std::cout << "Follow me on Twitter: @jakedothow\n\n";
		std::cout << "Starting Puma webserver\n";
#else
		std::cout << "Starting Puma " << service << ". Compiled on " << __DATE__ << ".\n";
		std::cout << "Follow me on Twitter: @jakedothow\n\n";
#endif

		// Configure logging
		app.set_logger([](const Request& rq, const Response& res)
		{
			std::string log = "New " + rq.method + " request. Path: " + rq.path + " Response: " + std::to_string(res.status);
			std::cout << log << "\n";
		});

		// Configure endpoints
		FortniteGame::init(&app);
		Lightswitch::init(&app);
		WaitingRoom::init(&app);
		OAuth::init(&app);
		Profile::init(&app);
		Cloudstorage::init(&app);

		std::cout << "Listening on 127.0.0.1:8010 :)\n";
		app.listen("127.0.0.1", 8010);
	}

	void setCallback(void* callback)
	{
		Session::QueryProfileCallback = callback;
	}

	void disableEmergencyNotice()
	{
		Session::EmergencyNotice.IsEnabled = false;
		Session::EmergencyNotice.Title = "";
		Session::EmergencyNotice.Body = "";
	}

	void setEmergencyNotice(std::string title, std::string body)
	{
		Session::EmergencyNotice.IsEnabled = true;
		Session::EmergencyNotice.Title = title;
		Session::EmergencyNotice.Body = body;
	}
}