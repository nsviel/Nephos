#pragma once

#include <string>
#include <thread>


namespace thr{

std::thread::id get_ID();
std::string get_ID_str();

}
