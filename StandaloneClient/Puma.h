#pragma once

#include <iostream>

namespace Puma
{
    void start(std::string service);
    void setCallback(void* callback);
    void disableEmergencyNotice();
    void setEmergencyNotice(std::string title, std::string body);
}