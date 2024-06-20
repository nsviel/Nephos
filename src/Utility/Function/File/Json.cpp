#include "Json.h"

#include <Utility/Namespace.h>
#include <iostream>
#include <fstream>
#include <string>


namespace utl::json{

nlohmann::json read_json(const std::string& path){
  //---------------------------

  std::ifstream file(path);
  if(!file.is_open()){
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

  // Read JSON data from file
  nlohmann::json data = read_json(path);

  // Split the key by dots
  std::istringstream keyStream(key);
  std::string segment;
  nlohmann::json* current = &data;

  while(std::getline(keyStream, segment, '.')){
    // If the segment does not exist, create a new nested JSON object
    if(!current->contains(segment)){
      (*current)[segment] = nlohmann::json::object();
    }
    // Move to the next level
    current = &(*current)[segment];
  }

  // Set the value at the final nested level
  *current = value;

  // Write JSON to file
  std::ofstream file(path);
  file << std::setw(4) << data << std::endl;

  //---------------------------
}
template<typename T> T read_value(const std::string& path, std::string key){
  T result;
  //---------------------------

  // Read JSON data from file
  std::ifstream file(path);
  if(!file.is_open()){
    std::cerr << "[Error] File " << path << " does not exist." << std::endl;
    return result; // Return default-constructed result
  }

  nlohmann::json j;
  file >> j;

  // Split the key by dots
  std::istringstream keyStream(key);
  std::string segment;
  nlohmann::json* current = &j;

  while(std::getline(keyStream, segment, '.')){
    // Check if the segment exists
    if(!current->contains(segment)){
      std::cerr << "[Error] Key segment '" << segment << "' not found in JSON file." << std::endl;
      return result; // Return default-constructed result
    }
    // Move to the next level
    current = &(*current)[segment];
  }

  // Try to parse the value at the final nested level into the result
  try{
    result = current->get<T>();
  }catch (const std::exception& e){
    std::cerr << "[Error] Failed to parse value for key '" << key << "': " << e.what() << std::endl;
  }

  //---------------------------
  return result;
}
bool is_json_file(const std::string& path){
  //---------------------------

  std::string extension = std::filesystem::path(path).extension();

  //---------------------------
  return (extension == ".json");
}

}
