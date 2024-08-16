#pragma once

#include <string>
#include <thread>


namespace sys::thread{

std::thread::id get_ID();
std::string get_ID_str();

}
