#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Capture/K4N/Namespace.h>

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

  //Subfunction
  bool is_json_file(const std::string& path);

private:

};

}
