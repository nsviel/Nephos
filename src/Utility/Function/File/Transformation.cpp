#include "File.h"

#include <Utility/Function/File/Json.h>
#include <iostream>
#include <fstream>


namespace utl::transformation{

glm::mat4 find_transformation_from_file(std::string path){
  //---------------------------

  if(path == ""){
    return glm::mat4(1);
  }
  else if(!utl::file::is_exist(path)){
    std::cout<<"[error] file at ["<<path<<"] does not exists"<<std::endl;
    return glm::mat4(1);
  }
  else if(utl::json::is_json_file(path) == false){
    std::cout<<"[error] file at ["<<path<<"] is not a json file"<<std::endl;
    return glm::mat4(1);
  }

  // Read the JSON file
  std::ifstream file(path);

  if(!file.is_open()){
    std::cerr << "Failed to open the JSON file." << std::endl;
    return glm::mat4(1);
  }

  // Parse the JSON data
  nlohmann::json j;
  file >> j;

  glm::mat4 mat = glm::mat4(1);
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

  //---------------------------
  return mat;
}
void save_transformation_to_file(glm::mat4& mat, std::string path){
  //---------------------------

  // Create a JSON object to store the matrix values
  nlohmann::json j;
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
  if(file.is_open()){
    file << j.dump(4); // Use dump(4) for pretty printing with an indentation of 4 spaces
    file.close();
  }else{
    std::cerr << "Failed to open the file for writing." << std::endl;
  }

  //---------------------------
}
void make_transformation_identity(glm::mat4& mat){
  //---------------------------

  mat = glm::mat4(1.0f);

  //---------------------------
}
void apply_transformation_capture(glm::mat4& mat){
    //---------------------------

    mat = glm::mat4(1.0f);
    mat[2][3] = 1;

    //---------------------------
  }

}
