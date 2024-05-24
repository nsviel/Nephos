#pragma once

#include <Utility/Specific/Common.h>

namespace k4n::dev{class Sensor;}


namespace k4n::utils{

class Data
{
public:
  //Constructor / Destructor
  Data();
  ~Data();

public:
  //Data function
  void convert_uint8_to_vec_uint16(const uint8_t* input, size_t size, std::vector<uint16_t>& output);

  //IR function
  void convert_ir_into_color(k4n::dev::Sensor* sensor);
  void find_ir_level(k4n::dev::Sensor* sensor);

  //Depth function
  vec3 convert_depth_2d_to_3d(k4n::dev::Sensor* sensor, ivec2 point_2d);
  void convert_depth_into_color(k4n::dev::Sensor* sensor, std::vector<uint8_t>& output);
  void find_depth_mode_range(k4n::dev::Sensor* sensor);

  //Normal function
  void make_normal_from_depth_image(k4n::dev::Sensor* sensor);
  void convert_normal_into_color(k4n::dev::Sensor* sensor, std::vector<glm::vec3>& vec_Nxyz);

private:

};

}
