#pragma once

#include "Common.h"

namespace Puma::Lightswitch {
	Json LightswitchResponse = R"(
		[{
			"serviceInstanceId": "fortnite",
			"status": "UP",
			"message": "Rift is UP",
			"maintenanceUri": null,
			"allowedActions": [],
			"banned": false
		}]
	)"_json;

	void init(Server* app) 
	{
		app->Get("/lightswitch/api/service/bulk/status", [](const Request& request, Response& response) 
		{
			response.set_content(LightswitchResponse.dump(), "application/json");
		});

		app->Get("/fortnite/api/storefront/v2/keychain", [](const Request& request, Response& response)
		{
			response.set_content("[\"hello\"]", "application/json");
		});
	}
}
