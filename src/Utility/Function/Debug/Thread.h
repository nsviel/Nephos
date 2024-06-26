#pragma once

#include <string>
#include <thread>


namespace utl::thread{

std::thread::id get_ID();
std::string get_ID_str();

}
