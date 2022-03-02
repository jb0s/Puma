#pragma once

#include "Common.h"

namespace Puma::Cloudstorage
{
	void init(Server* app)
	{
		app->Get("/fortnite/api/cloudstorage/system", [](const Request& request, Response& response)
		{
			response.set_content("[]", "application/json");
		});

		app->Get(R"(/fortnite/api/cloudstorage/user/(.*)/(.*))", [](const Request& request, Response& response)
		{
			response.set_content("", "application/octet-stream");
		});
	}
}
