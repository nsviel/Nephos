#include "Json.h"

#include <iostream>
#include <fstream>


namespace utl::json{

nlohmann::json read_json(const std::string& path){
  //---------------------------

  std::ifstream file(path);
  if (!file.is_open()) {
    std::cerr << "[error] File " << path << " does not exist." << std::endl;
    return nlohmann::json();
  }

  // Check if the file is empty
  if(file.peek() == std::ifstream::traits_type::eof()){
    return nlohmann::json();
  }

  nlohmann::json j;
  file >> j;

  //---------------------------
  return j;
}
template<typename T> void write_value(const std::string& path, const std::string& key, const T& value){
  //---------------------------

  nlohmann::json data = read_json(path);
  if(data.empty()) return;

  // Check if the key contains a subkey using dot notation
  size_t dotIndex = key.find('.');
  if(dotIndex != std::string::npos) {
    std::string parentKey = key.substr(0, dotIndex);
    std::string subKey = key.substr(dotIndex + 1);
    if (data.contains(parentKey)) {
      // If the parent key exists, access the subkey and assign the value
      data[parentKey][subKey] = value;
    } else {
      // If the parent key does not exist, create it and assign the subkey with the value
      data[parentKey] = nlohmann::json::object();
      data[parentKey][subKey] = value;
    }
  } else {
    // Modify JSON data
    data[key] = value;
  }

  // Write JSON to file
  std::ofstream file(path);
  file << std::setw(4) << data << std::endl;

  //---------------------------
}

}
