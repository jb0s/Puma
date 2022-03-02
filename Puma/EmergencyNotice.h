#pragma once

#include <iostream>

namespace Puma::Models::Internal
{
	struct EmergencyNotice
	{
	public:
		bool IsEnabled = true;
		std::string Title = "Puma";
		std::string Body = "Welcome to Puma!";
	};
}