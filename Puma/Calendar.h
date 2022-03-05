#pragma once

#include "Common.h"
#include "CalendarUtils.h"

namespace Puma::Calendar
{
	Json CalendarResponse = R"(
	{
		"channels":{
			"standalone-store":{
				"states":[
					{
						"validFrom":"0001-01-01T00:00:00.000Z",
						"activeEvents":[
						],
						"state":{
							"activePurchaseLimitingEventIds":[
							
							],
							"storefront":{
							
							},
							"rmtPromotionConfig":[
							
							],
							"storeEnd":"0001-01-01T00:00:00.000Z"
						}
					}
				],
				"cacheExpire":"0001-01-01T00:00:00.000Z"
			},
			"client-events":{
				"states":[
					{
						"validFrom":"0001-01-01T00:00:00.000Z",
						"activeEvents":[
							{
								"eventType":"EventFlag.LobbySeason0",
								"activeUntil":"9999-12-31T23:59:59.999Z",
								"activeSince":"0001-01-01T00:00:00.000Z"
							}
						],
						"state":{
							"activeStorefronts":[
							],
							"eventNamedWeights":{
							},
							"seasonNumber":0,
							"seasonTemplateId":"AthenaSeason:athenaseason0",
							"matchXpBonusPoints":0.0,
							"eventPunchCardTemplateId":"",
							"seasonBegin":"0001-01-01T00:00:00.000Z",
							"seasonEnd":"9999-12-31T23:59:59.999Z",
							"seasonDisplayedEnd":"9999-12-31T23:59:59.999Z",
							"weeklyStoreEnd":"9999-12-31T23:59:59.999Z",
							"dailyStoreEnd":"9999-12-31T23:59:59.999Z",
							"stwDailyStoreEnd":"9999-12-31T23:59:59.999Z",
							"stwEventStoreEnd":"9999-12-31T23:59:59.999Z",
							"stwWeeklyStoreEnd":"9999-12-31T23:59:59.999Z",
							"sectionStoreEnds":{
							}
						}
					}
				],
				"cacheExpire":"9999-12-31T23:59:59.999Z"
			}
		},
		"currentTime":"0001-01-01T00:00:00.000Z",
		"cacheIntervalMins":15.0
	}
	)"_json;

	void init(Server* app)
	{
		app->Get("/fortnite/api/calendar/v1/timeline", [](const Request& request, Response& response)
		{
			Json calendar = CalendarResponse;
			std::string seasonNumber = CalendarUtils::getSeasonNumber(request.get_header_value("User-Agent"));

			// Set season background
			if (seasonNumber == "2.00")
			{
				calendar["channels"]["client-events"]["states"][0]["activeEvents"][0]["eventType"] = "EventFlag.LobbyWinterDecor";
			}
			else
			{
				calendar["channels"]["client-events"]["states"][0]["activeEvents"][0]["eventType"] = "EventFlag.LobbySeason" + seasonNumber.substr(0, seasonNumber.find("."));
			}

			// Set season number
			calendar["channels"]["client-events"]["states"][0]["state"]["seasonTemplateId"] = "AthenaSeason:athenaseason" + seasonNumber.substr(0, seasonNumber.find("."));
			calendar["channels"]["client-events"]["states"][0]["state"]["seasonNumber"] = std::stoi(seasonNumber);

			response.set_content(calendar.dump(), "application/json");
		});
	}
}
