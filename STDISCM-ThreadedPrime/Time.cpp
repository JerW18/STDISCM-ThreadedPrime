#include <chrono>
#include <iomanip>
#include <sstream>

#include "Time.h"

string Time::getTime() 
{
    auto now = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(now);

    tm buf;
    localtime_s(&buf, &now_c);

    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    ostringstream oss;
    oss << std::put_time(&buf, "%Y-%m-%d %H:%M:%S") << "." << std::setw(3) << std::setfill('0') << ms.count();

    return oss.str();
}
