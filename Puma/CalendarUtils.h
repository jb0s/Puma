#pragma once

#include <iostream>
#include <string>

namespace Puma::CalendarUtils
{
	std::string getSeasonNumber(std::string userAgent)
	{
		if (userAgent.find("Fortnite") == std::string::npos)
		{
			return "1.8";
		}

		std::string trim = userAgent.substr(userAgent.find("-") + 1, userAgent.find("."));
		std::string buildId = trim.substr(0, trim.find("-"));
		if (buildId == "Next" || buildId == "Cert" || buildId.find("+++Fortnite+Release") != std::string::npos)
		{
			return "2.0";
		}

		return buildId;
	}
}