#pragma once

#include <Utility/Specific/common.h>

namespace k4n::dev{class Sensor;}


namespace k4n::utils{

class Transformation
{
public:
  //Constructor / Destructor
  Transformation();
  ~Transformation();

public:
  //Main function
  void find_transformation_from_file(k4n::dev::Sensor* sensor, string path);
  void save_transformation_to_file(k4n::dev::Sensor* sensor);
  void make_transformation_identity(k4n::dev::Sensor* sensor);
  void apply_transformation_capture(k4n::dev::Sensor* sensor);
  vec3 convert_depth_2d_to_3d(k4n::dev::Sensor* sensor, ivec2 point_2d);

  //Subfunction
  bool is_json_file(const std::string& path);

private:

};

}
