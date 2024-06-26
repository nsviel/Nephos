#include "Thread.h"

#include <iostream>
#include <sstream>


namespace utl::thread{

std::thread::id get_ID(){
  //---------------------------

  return std::this_thread::get_id();

  //---------------------------
}
std::string get_ID_str(){
  std::stringstream ss;
  //---------------------------

  ss << std::this_thread::get_id();

  //---------------------------
  return ss.str();
}

}
