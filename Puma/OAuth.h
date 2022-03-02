#pragma once

#include "Common.h"
#include "Session.h"

namespace Puma::OAuth
{
	void init(Server* app)
	{
		app->Post("/account/api/oauth/token", [](const Request& request, Response& response)
		{
			if (request.has_param("grant_type"))
			{
				if (request.get_param_value("grant_type") == "client_credentials")
				{
					Json clientCredResponse = {
						{"access_token", "H3YM8H0P3URD01NGW3LLTHX4US1NPUMA"},
						{"expires_in", 28800},
						{"expires_at", "9999-12-31T23:59:59.999Z"},
						{"token_type", "bearer"},
						{"client_id", "puma"},
						{"internal_client", "true"},
						{"client_service", "fortnite"}
					};

					response.set_content(clientCredResponse.dump(), "application/json");
				}
				else
				{
					std::string email = request.get_param_value("username");
					std::string username = email.substr(0, email.find("@"));
					Session::DisplayName = username;

					Json accountResponse = {
						{"access_token", "H3YM8H0P3URD01NGW3LLTHX4US1NPUMA"},
						{"expires_in", 28800},
						{"expires_at", "9999-12-31T23:59:59.999Z"},
						{"token_type", "bearer"},
						{"account_id", "pumauser0"},
						{"client_id", "puma"},
						{"internal_client", true},
						{"client_service", "fortnite"},
						{"displayName", Session::DisplayName},
						{"app", "fortnite"},
						{"in_app_id", Session::DisplayName},
						{"device_id", "pumadevice0"}
					};

					response.set_content(accountResponse.dump(), "application/json");
				}
			}
			else
			{
				response.status = 400;
				//response.set_content(Errors::InvalidRequest.dump(), "application/json");
			}
		});

		app->Get(R"(/account/api/public/account/(.*))", [](const Request& req, Response& res)
		{
			auto account_id = static_cast<std::string>(req.matches[1]);
			Json response = {
				{"id", account_id},
				{"displayName", Session::DisplayName},
				{"externalAuths", Json({})}
			};

			res.set_content(response.dump(), "application/json");
		});
	}
}
