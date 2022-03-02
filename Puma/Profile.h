#pragma once

#include "Common.h"
#include "Athena.h"

namespace Puma::Profile
{
	void init(Server* app)
	{
		app->Post(R"(/fortnite/api/game/v2/profile/(.*)/client/(.*))", [](const Request& request, Response& response)
		{
			Json profileData;
			std::string accountId = static_cast<std::string>(request.matches[1]);
			std::string action = static_cast<std::string>(request.matches[2]);
			std::string profileId = "common_core";
			int revision = 0;

			if (request.has_param("rvn"))
			{
				revision = std::stoi(request.get_param_value("rvn"));
			}
			if (request.has_param("profileId"))
			{
				profileId = request.get_param_value("profileId");
			}

			if (profileId == "athena")
			{
				if (Session::QueryProfileCallback != nullptr)
				{
					((void(*)())Session::QueryProfileCallback)();
					Session::QueryProfileCallback = nullptr;
				}

				profileData = Athena::AthenaProfile;
			}

			if (profileData["rvn"].is_null())
			{
				profileData["rvn"] = 1;
			}
			if (profileData["commandRevision"].is_null())
			{
				profileData["commandRevision"] = 1;
			}

			Json res = {
				{"profileRevision", profileData["rvn"]},
				{"profileId", profileId},
				{"profileChangesBaseRevision", profileData["rvn"]},
				{"profileCommandRevision", profileData["commandRevision"]},
				{"responseVersion", 1}
			};

			response.set_content(res.dump(), "application/json");
		});
	}
}