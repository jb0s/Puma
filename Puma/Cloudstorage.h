#pragma once

#include <filesystem>
#include <iostream>
#include <fstream>
#include "Common.h"
#include "CalendarUtils.h"

namespace Puma::Cloudstorage
{
	std::string DefaultEngine = "[/Script/FortniteGame.FortPlayerController]\nTurboBuildInterval = 0.005f\nTurboBuildFirstInterval = 0.005f\nbClientSideEditPrediction = false";
	std::string DefaultInput = "[/Script/Engine.InputSettings]\n+ConsoleKeys=Tilde\n+ConsoleKeys=F8)";

	void init(Server* app)
	{
		app->Get("/fortnite/api/cloudstorage/system", [](const Request& request, Response& response)
		{
			Json content = Json::array({
				{
					{"uniqueFileName", "DefaultEngine.ini"},
					{"filename", "DefaultEngine.ini"},
					{"hash", "DefaultEngine-r2"},
					{"hash256", "DefaultEngine-r2"},
					{"length", DefaultEngine.size()},
					{"contentType", "application/octet-stream"},
					{"storageType", "S3"},
					{"doNotCache", false}
				},
				{
					{"uniqueFileName", "DefaultInput.ini"},
					{"filename", "DefaultInput.ini"},
					{"hash", "DefaultInput-r2"},
					{"hash256", "DefaultInput-r2"},
					{"length", DefaultInput.size()},
					{"contentType", "application/octet-stream"},
					{"storageType", "S3"},
					{"doNotCache", false}
				}
			});

			response.set_content(content.dump(), "application/json");
		});

		app->Get("/fortnite/api/cloudstorage/system/DefaultEngine.ini", [](const Request& request, Response& response)
		{
			response.set_content(DefaultEngine, "application/octet-stream");
		});

		app->Get("/fortnite/api/cloudstorage/system/DefaultInput.ini", [](const Request& request, Response& response)
		{
			response.set_content(DefaultInput, "application/octet-stream");
		});

		app->Get(R"(/fortnite/api/cloudstorage/user/(.*)/ClientSettings.Sav)", [](const Request& request, Response& response)
		{
			std::string buildName = CalendarUtils::getSeasonNumber(request.get_header_value("User-Agent"));
			auto path = std::filesystem::temp_directory_path().parent_path().parent_path();
			path /= "Rift\\ClientSettings-" + buildName + ".Sav";

			std::ifstream config(path);
			std::stringstream content;
			content << config.rdbuf();

			response.set_content(content.str(), "application/octet-stream");
		});

		app->Get(R"(/fortnite/api/cloudstorage/user/(.*))", [](const Request& request, Response& response)
		{
			std::string buildName = CalendarUtils::getSeasonNumber(request.get_header_value("User-Agent"));
			auto path = std::filesystem::temp_directory_path().parent_path().parent_path();
			path /= "Rift\\ClientSettings-" + buildName + ".Sav";

			std::ifstream config(path);
			std::stringstream content;
			content << config.rdbuf();

			Json json = Json::array({
				{
					{"uniqueFileName", "ClientSettings.Sav"},
					{"filename", "ClientSettings.Sav"},
					{"hash", "ClientSettings"},
					{"hash256", "ClientSettings"},
					{"length", content.str().size()},
					{"contentType", "application/octet-stream"},
					{"storageType", "S3"},
					{"doNotCache", false}
				}
			});

			response.set_content(json.dump(), "application/json");
		});

		app->Put(R"(/fortnite/api/cloudstorage/user/(.*)/(.*))", [](const Request& request, Response& response)
		{
			std::string buildName = CalendarUtils::getSeasonNumber(request.get_header_value("User-Agent"));
			auto path = std::filesystem::temp_directory_path().parent_path().parent_path();
			path /= "Rift\\ClientSettings-" + buildName + ".Sav";

			std::ofstream save;

			save.open(path);
			save.clear();
			save << request.body;
			save.close();
		});
	}
}
