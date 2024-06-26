#pragma once

#include <string>


namespace thread{

std::string get_ID(){
  //---------------------------

  return std::stringstream{} << std::this_thread::get_id()).str();

  //---------------------------
}

}
