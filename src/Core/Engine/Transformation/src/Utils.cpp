#include "Utils.h"

#include <Utility/Namespace.h>
#include <glm/gtc/matrix_transform.hpp>


namespace eng::trf{

// Constructor / Destructor
Utils::Utils(){}
Utils::~Utils(){}

//Main function
glm::mat4 Utils::get_translation_mat(glm::vec3 trans){
  glm::mat4 translation(1.0);
  //---------------------------

  translation[0][3] = trans.x;
  translation[1][3] = trans.y;
  translation[2][3] = trans.z;

  //---------------------------
  return translation;
}
glm::mat4 Utils::get_translation_mat_neye(glm::vec3 trans){
  glm::mat4 translation(0.0);
  //---------------------------

  translation[0][3] = trans.x;
  translation[1][3] = trans.y;
  translation[2][3] = trans.z;

  //---------------------------
  return translation;
}
glm::mat4 Utils::get_rotation_mat(glm::vec3 r){
  glm::mat4 Rx(1.0);
  glm::mat4 Ry(1.0);
  glm::mat4 Rz(1.0);
  //---------------------------

  Rx[1][1]=cos(r.x);
  Rx[2][1]=sin(r.x);
  Rx[1][2]=-sin(r.x);
  Rx[2][2]=cos(r.x);

  Ry[0][0]=cos(r.y);
  Ry[0][2]=sin(r.y);
  Ry[2][0]=-sin(r.y);
  Ry[2][2]=cos(r.y);

  Rz[0][0]=cos(r.z);
  Rz[1][0]=sin(r.z);
  Rz[0][1]=-sin(r.z);
  Rz[1][1]=cos(r.z);

  glm::mat4 rotation = Rx * Ry * Rz;

  //---------------------------
  return rotation;
}
glm::mat4 Utils::find_transformation_from_file(std::string path){
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
void Utils::save_transformation_to_file(glm::mat4& mat, std::string path){
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
void Utils::make_transformation_identity(glm::mat4& mat){
  //---------------------------

  mat = glm::mat4(1.0f);

  //---------------------------
}
void Utils::init_and_heighten_transformation(glm::mat4& mat, float value){
  //---------------------------

  mat = glm::mat4(1.0f);
  mat[2][3] = value;

  //---------------------------
}

}