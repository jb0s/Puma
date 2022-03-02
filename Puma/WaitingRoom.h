#pragma once

#include "Common.h"

namespace Puma::WaitingRoom
{
	void init(Server* app)
	{
		app->Get("/waitingroom/api/waitingroom", [](const Request& request, Response& response)
		{
			response.status = 204;
		});
	}
}
