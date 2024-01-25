#pragma once

#include <Utility/Specific/common.h>

namespace eng::k4n::dev{class Sensor;}


namespace eng::k4n::utils{

class Transformation
{
public:
  //Constructor / Destructor
  Transformation();
  ~Transformation();

public:
  //Main function
  void find_transformation_from_file(eng::k4n::dev::Sensor* sensor, string path);
  void save_transformation_to_file(eng::k4n::dev::Sensor* sensor);
  void make_transformation_identity(eng::k4n::dev::Sensor* sensor);

  //Subfunction
  bool is_json_file(const std::string& path);

private:

};

}
