#pragma once

#include "Session.h"

namespace Puma::Preferences
{
	void disableEmergencyNotice()
	{
		Session::EmergencyNotice.IsEnabled = false;
		Session::EmergencyNotice.Title = "";
		Session::EmergencyNotice.Body = "";
	}

	void setEmergencyNotice(std::string title, std::string body)
	{
		Session::EmergencyNotice.IsEnabled = true;
		Session::EmergencyNotice.Title = title;
		Session::EmergencyNotice.Body = body;
	}
}