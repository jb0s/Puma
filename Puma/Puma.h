#pragma once
#define DEVELOPMENT_MODE

#include "Common.h"
#include "Errors.h"
#include "FortniteGame.h"
#include "Lightswitch.h"
#include "WaitingRoom.h"
#include "OAuth.h"
#include "Athena.h"
#include "Profile.h"
#include "Cloudstorage.h"
#include "Session.h"

namespace Puma
{
    inline Server app;
	void start(std::string service);
	void setCallback(void* callback);
	void disableEmergencyNotice();
	void setEmergencyNotice(std::string title, std::string body);
}