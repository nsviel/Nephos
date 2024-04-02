#include "File.h"

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>


namespace utl::json{

nlohmann::json read_json(const std::string& path){
  //---------------------------

  std::ifstream file(path);
  nlohmann::json j;
  file >> j;

  //---------------------------
  return j;
}

template<typename T>
void write_json(const std::string& path, const std::string& key, const T& value){
  //---------------------------

  nlohmann::json data = read_json(path);

  // Modify JSON data
  data[key] = value;

  // Write JSON to file
  std::ofstream file(path);
  file << std::setw(4) << data << std::endl;

  //---------------------------
}

}
