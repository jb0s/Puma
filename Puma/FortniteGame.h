#pragma once

#include "Common.h"
#include "Session.h"

namespace Puma::FortniteGame
{
	Json FortniteGameResponse = R"(
	{
		"_title": "{TITLE}",
		"_locale": "en-US",
		"lastModified": "2022-02-28T06:38:50.565Z",
		"battleroyalenews": {
			"_title": "battleroyalenews",
			"news": {
				"messages": [
				],
				"motds": [
				]
			},
			"_locale": "en-US",
			"lastModified": "2022-02-28T06:38:50.566Z"
		},
		"battleroyalenewsv2": {
			"_title": "battleroyalenews",
			"news": {
				"messages": [
				],
				"motds": [
				]
			},
			"_locale": "en-US",
			"lastModified": "2022-02-28T06:38:50.566Z"
		},
		"emergencynotice": {
			"_title": "emergencynotice",
			"news": {
				"messages": [{
						"_type": "CommonUI Simple Message Base",
						"image": null,
						"hidden": false,
						"messagetype": "normal",
						"title": "{TITLE}",
						"body": "{BODY}",
						"spotlight": false
					}
				],
				"motds": [
				]
			},
			"_locale": "en-US",
			"lastModified": "2022-02-28T06:38:50.568Z"
		},
		"emergencynoticev2": {
			"_title": "emergencynotice",
			"news": {
				"messages": [{
						"_type": "CommonUI Simple Message Base",
						"image": null,
						"hidden": false,
						"messagetype": "normal",
						"title": "{TITLE}",
						"body": "{BODY}",
						"spotlight": false
					}
				],
				"motds": [
				]
			},
			"_locale": "en-US",
			"lastModified": "2022-02-28T06:38:50.568Z"
		},
		"subgameinfo": {
			"_title": "SubgameInfo",
			"_locale": "en-US",
			"lastModified": "2022-02-28T06:38:50.569Z",
			"battleroyale": {
				"_type": "Subgame Info",
				"image": "",
				"color": "000000",
				"specialMessage": null,
				"description": "100 Player PvP",
				"subgame": "battleroyale",
				"standardMessageLine2": null,
				"title": "Battle Royale",
				"standardMessageLine1": null
			},
			"savetheworld": {
				"_type": "Subgame Info",
				"image": "",
				"color": "7615E9FF",
				"specialMessage": null,
				"description": "Cooperative PvE Adventure",
				"subgame": "savetheworld",
				"standardMessageLine2": null,
				"title": "savetheworld",
				"standardMessageLine1": null
			},
			"creative": {
				"_type": "Subgame Info",
				"image": "",
				"color": "13BDA1FF",
				"specialMessage": null,
				"description": "Your Islands. Your Friends. Your Rules.",
				"subgame": "creative",
				"standardMessageLine2": null,
				"title": "",
				"standardMessageLine1": null
			}
		},
		"subgameselectdata": {
			"_title": "subgameselectdata",
			"saveTheWorldUnowned": {
				"_type": "CommonUI Simple Message",
				"message": {
					"_type": "CommonUI Simple Message Base",
					"image": "",
					"hidden": false,
					"messagetype": "normal",
					"title": "Co-op PvE",
					"body": "Cooperative PvE storm-fighting adventure!",
					"spotlight": false
				}
			},
			"battleRoyale": {
				"_type": "CommonUI Simple Message",
				"message": {
					"_type": "CommonUI Simple Message Base",
					"image": "",
					"hidden": false,
					"messagetype": "normal",
					"title": "100 Player PvP",
					"body": "100 Player PvP Battle Royale.\n\nPvE Progress does not affect Battle Royale.",
					"spotlight": false
				}
			},
			"creative": {
				"_type": "CommonUI Simple Message",
				"message": {
					"_type": "CommonUI Simple Message Base",
					"image": "",
					"hidden": false,
					"messagetype": "normal",
					"title": "NEW - Build Your Own Island!",
					"body": "Create your own unique games and play with your friends!",
					"spotlight": false
				}
			},
			"saveTheWorld": {
				"_type": "CommonUI Simple Message",
				"message": {
					"_type": "CommonUI Simple Message Base",
					"image": "",
					"hidden": false,
					"messagetype": "normal",
					"title": "Co-op PvE",
					"body": "Cooperative PvE storm-fighting adventure!",
					"spotlight": false
				}
			},
			"lastModified": "2022-02-28T06:38:50.569Z",
			"_locale": "en-US"
		},
		"dynamicbackgrounds": {
			"_title": "dynamicbackgrounds",
			"backgrounds": {
				"backgrounds": [{
						"stage": "season1",
						"key": "lobby",
						"_type": "DynamicBackground"
					},{
						"stage": "season1",
						"key": "vault",
						"_type": "DynamicBackground"
					}
				],
				"_type": "DynamicBackgroundList"
			},
			"_locale": "en-US",
			"lastModified": "2022-02-28T06:38:50.570Z"
		}
	}
	)"_json;

	void init(Server* app) 
	{
		app->Get("/content/api/pages/fortnite-game", [](const Request& rq, Response& rs) 
		{
			Json res = FortniteGameResponse;
			res["_title"] = "Fortnite Game on Puma " + Session::ServiceName;
			if (Session::EmergencyNotice.IsEnabled)
			{
				res["emergencynotice"]["news"]["messages"][0]["title"] = Session::EmergencyNotice.Title;
				res["emergencynotice"]["news"]["messages"][0]["body"] = Session::EmergencyNotice.Body;
				res["emergencynoticev2"]["news"]["messages"][0]["title"] = Session::EmergencyNotice.Title;
				res["emergencynoticev2"]["news"]["messages"][0]["body"] = Session::EmergencyNotice.Body;
			}
			else
			{
				res["emergencynotice"] = NULL;
				res["emergencynoticev2"] = NULL;
			}

			rs.set_content(res.dump(), "application/json");
		});

		app->Get("/fortnite/api/game/v2/enabled_features", [](const Request& req, Response& res)
		{
			res.set_content("[]", "application/json");
		});

		app->Post(R"(/fortnite/api/game/v2/tryPlayOnPlatform/account/(.*))", [](const Request& req, Response& res)
		{
			res.set_content("true", "text/plain");
		});
	}
}