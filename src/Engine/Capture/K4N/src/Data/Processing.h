#pragma once

#include <Utility/Specific/common.h>

namespace k4n::dev{class Sensor;}
namespace eng::ope{class Voxelizer;}
namespace eng::ope{class Triangulation;}
namespace ope::color{class Colorizer;}


namespace k4n::data{

class Processing
{
public:
  //Constructor / Destructor
  Processing();
  ~Processing();

public:
  //Main function
  void start_thread(k4n::dev::Sensor* sensor);
  void run_thread(k4n::dev::Sensor* sensor);

  //Subfunction
  void voxelize_object(k4n::dev::Sensor* sensor);
  void triangularize_object(k4n::dev::Sensor* sensor);
  void update_object(k4n::dev::Sensor* sensor);

private:
  eng::ope::Voxelizer* ope_voxelizer;
  eng::ope::Triangulation* ope_trianguler;
  ope::color::Colorizer* ope_colorizer;

  std::thread thread;
};

}
