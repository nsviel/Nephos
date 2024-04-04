#include "Json.h"

#include <iostream>
#include <fstream>
#include <string>


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
template<typename T> T read_value(const std::string& path, std::string key){
  T result;
  //---------------------------

  std::ifstream file(path);
  if (!file.is_open()) {
    std::cerr << "[Error] File " << path << " does not exist." << std::endl;
    return result; // Return default-constructed result
  }

  nlohmann::json j;
  file >> j;

  // Split the key into parent and subkey (if it contains a dot)
  size_t dotIndex = key.find('.');
  if (dotIndex != std::string::npos) {
    std::string parentKey = key.substr(0, dotIndex);
    std::string subKey = key.substr(dotIndex + 1);

    // Check if the parent key exists in the JSON object
    if (j.find(parentKey) == j.end()) {
      std::cerr << "[Error] Parent key '" << parentKey << "' not found in JSON file." << std::endl;
      return result; // Return default-constructed result
    }

    // Extract the parent JSON object
    nlohmann::json parentObject = j[parentKey];
    result = parentObject[subKey].get<T>();
  } else {
    // Check if the key exists in the JSON object
    if (j.find(key) == j.end()) {
      std::cerr << "[Error] Key '" << key << "' not found in JSON file." << std::endl;
      return result; // Return default-constructed result
    }

    // Try to parse the value associated with the key into the result
    try {
      result = j[key].get<T>();
    } catch (const std::exception& e) {
      std::cerr << "[Error] Failed to parse value for key '" << key << "': " << e.what() << std::endl;
    }
  }

  //---------------------------
  return result;
}

}