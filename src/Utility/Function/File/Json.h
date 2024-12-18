#pragma once

#include <Utility/Function/File/File.h>
#include <nlohmann/json.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

namespace utl::json{

// Main function
void write_value(const std::string& path, std::string key, const bool& value);
void read_value(const std::string& path, const std::string& key, bool& value);

// Subfunctions
nlohmann::json read_json(const std::string& path);
bool is_json_file(const std::string& path);

// Template function
template<typename T>
T template_null(const T& value){
  //---------------------------

  // Return a null value for the type T
  if constexpr (std::is_arithmetic_v<T>){
    return static_cast<T>(0);  // For numeric types
  } else if constexpr (std::is_same_v<T, std::string>){
    return "";  // For std::string
  }else{
    return T();  // For other types, return default-constructed T
  }

  //---------------------------
}
template<typename T>
void write_value(const std::string& path, std::string key, const T& value){
  //---------------------------

  // Read JSON data from file
  nlohmann::json data = utl::json::read_json(path);

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
template<typename T>
T read_value(const std::string& path, std::string key){
  T result = template_null<T>(result);
  //---------------------------

  if(!utl::file::is_exist(path)) return result;

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
  } catch(const std::exception& e){
    std::cerr << "[Error] Failed to parse value for key '" << key << "': " << e.what() << std::endl;
  }

  //---------------------------
  return result;
}

}
