#include "Transformation.h"

#include <Kinect/Namespace.h>
#include <Utility/Namespace.h>
#include <nlohmann/json.hpp>
#include <filesystem>


namespace k4n::utils{

//Constructor / Destructor
Transformation::Transformation(){
  //---------------------------


  //---------------------------
}
Transformation::~Transformation(){}

//Main function
void Transformation::find_transformation_from_file(k4n::dev::Sensor* sensor, string path){
  if(path != "" && !utl::file::is_exist(path)) return;
  //---------------------------

  if(is_json_file(path) == false) return;

  // Read the JSON file
  std::ifstream file(path);

  if (!file.is_open()) {
    std::cerr << "Failed to open the JSON file." << std::endl;
    return;
  }

  // Parse the JSON data
  nlohmann::json j;
  file >> j;

  mat4 mat = mat4(1);
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
  string& path = sensor->param.path.transformation;
  mat4& mat = sensor->get_pose()->model;
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
  if (file.is_open()) {
    file << j.dump(4); // Use dump(4) for pretty printing with an indentation of 4 spaces
    file.close();
  } else {
    std::cerr << "Failed to open the file for writing." << std::endl;
  }

  //---------------------------
}
void Transformation::make_transformation_identity(k4n::dev::Sensor* sensor){
  utl::type::Pose* pose = sensor->get_pose();
  //---------------------------

  pose->model = mat4(1.0f);

  //---------------------------
}
void Transformation::apply_transformation_capture(k4n::dev::Sensor* sensor){
  utl::type::Pose* pose = sensor->get_pose();
  //---------------------------

  pose->model = mat4(1.0f);
  pose->model[2][3] = 1;

  //---------------------------
}
vec3 Transformation::convert_depth_2d_to_3d(k4n::dev::Sensor* sensor, ivec2 point_2d){
  //---------------------------

  uint16_t* buffer = reinterpret_cast<uint16_t*>(sensor->depth.data.buffer);
  int width = sensor->depth.data.width;

  //Retrieve image coordinates
  int x = point_2d[0];
  int y = point_2d[1];
  k4a_float2_t source_xy = { static_cast<float>(x), static_cast<float>(y) };
  float source_z = static_cast<float>(buffer[y * width + x]);

  //Convert it into 3D coordinate
  k4a_float3_t target_xyz;
  bool success = sensor->param.calibration.convert_2d_to_3d(source_xy, source_z, K4A_CALIBRATION_TYPE_DEPTH, K4A_CALIBRATION_TYPE_DEPTH, &target_xyz);
  vec4 xyzw = vec4(target_xyz.xyz.x, target_xyz.xyz.y, target_xyz.xyz.z, 1);

  //Apply transformation
  float inv_scale = 1.0f / 1000.0f;
  xyzw.x = -xyzw.x * inv_scale;
  xyzw.y = -xyzw.y * inv_scale;
  xyzw.z = xyzw.z * inv_scale;
  vec3 pose = vec3(xyzw.z, xyzw.x, xyzw.y);

  //---------------------------
  return pose;
}

//Subfunction
bool Transformation::is_json_file(const std::string& path){
  //---------------------------

  std::string extension = std::filesystem::path(path).extension();

  //---------------------------
  return (extension == ".json");
}

}