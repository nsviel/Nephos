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

//Main function
void Transformation::find_transformation_from_file(k4n::dev::Sensor* sensor){
  mat4 mat = mat4(1);
  string& path = sensor->param.path_transfo;
  //---------------------------

  if(is_json_file(path) == false) return;

  // Read the JSON file
  std::ifstream file(path);

  if (!file.is_open()) {
    std::cerr << "Failed to open the JSON file." << std::endl;
    return;
  }

  // Parse the JSON data
  json j;
  file >> j;

  mat[0][0] = j["m00"];
  mat[1][0] = j["m10"];
  mat[2][0] = j["m20"];
  mat[3][0] = j["m30"];

  mat[0][1] = j["m01"];
  mat[1][1] = j["m11"];
  mat[2][1] = j["m21"];
  mat[3][1] = j["m31"];

  mat[0][2] = j["m02"];
  mat[1][2] = j["m12"];
  mat[2][2] = j["m22"];
  mat[3][2] = j["m32"];

  mat[0][3] = j["m03"];
  mat[1][3] = j["m13"];
  mat[2][3] = j["m23"];
  mat[3][3] = j["m33"];

  utl::type::Pose* pose = sensor->get_pose();
  pose->model = mat;
  pose->model_init = mat;

  //---------------------------
}
void Transformation::save_transformation_to_file(k4n::dev::Sensor* sensor){
  string& path = sensor->param.path_transfo;
  mat4& mat = sensor->get_pose()->model;
  //---------------------------

  // Create a JSON object to store the matrix values
  json j;
  j["m00"] = mat[0][0];
  j["m10"] = mat[1][0];
  j["m20"] = mat[2][0];
  j["m30"] = mat[3][0];

  j["m01"] = mat[0][1];
  j["m11"] = mat[1][1];
  j["m21"] = mat[2][1];
  j["m31"] = mat[3][1];

  j["m02"] = mat[0][2];
  j["m12"] = mat[1][2];
  j["m22"] = mat[2][2];
  j["m32"] = mat[3][2];

  j["m03"] = mat[0][3];
  j["m13"] = mat[1][3];
  j["m23"] = mat[2][3];
  j["m33"] = mat[3][3];

  // Write the JSON object to the file
  std::ofstream file(path);
  if (file.is_open()) {
    file << j.dump(4); // Use dump(4) for pretty printing with an indentation of 4 spaces
    file.close();
  } else {
    std::cerr << "Failed to open the file for writing." << std::endl;
  }

  //---------------------------
}

//Subfunction
bool Transformation::is_json_file(const std::string& path){
  //---------------------------

  std::string extension = std::filesystem::path(path).extension();

  //---------------------------
  return (extension == ".json");
}

}
