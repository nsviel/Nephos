#include "Transformation.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;


namespace k4n::utils{

//Constructor / Destructor
Transformation::Transformation(){
  //---------------------------


  //---------------------------
}
Transformation::~Transformation(){}

mat4 Transformation::get_matrix_from_file(string path){
  mat4 mat = mat4(1);
  //---------------------------

  if(is_json_file(path) == false) return mat;

  // Read the JSON file
  std::ifstream file(path);

  if (!file.is_open()) {
    std::cerr << "Failed to open the JSON file." << std::endl;
    return mat;
  }

  // Parse the JSON data
  json j;
  file >> j;

  // Access the values
  double m00 = j["m00"];
  double m10 = j["m10"];
  // ... access other values similarly

  // Display the values
  std::cout << "m00: " << m00 << std::endl;
  std::cout << "m10: " << m10 << std::endl;
  // ... display other values similarly


  //---------------------------
  return mat;
}
bool Transformation::is_json_file(const std::string& path){
  //---------------------------

  std::string extension = std::filesystem::path(path).extension();

  //---------------------------
  return (extension == ".json");
}

}
