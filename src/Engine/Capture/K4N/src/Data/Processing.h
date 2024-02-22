#pragma once

#include <Utility/Specific/common.h>

namespace k4n::dev{class Sensor;}
namespace ope{class Voxelizer;}
namespace ope{class Triangulation;}
namespace ope::color{class Colorizer;}
namespace ope::attribut{class Normal;}


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
  void colorize_object(k4n::dev::Sensor* sensor);
  void voxelize_object(k4n::dev::Sensor* sensor);
  void triangularize_object(k4n::dev::Sensor* sensor);
  void update_object(k4n::dev::Sensor* sensor);

private:
  ope::Voxelizer* ope_voxelizer;
  ope::Triangulation* ope_trianguler;
  ope::color::Colorizer* ope_colorizer;
  ope::attribut::Normal* ope_normal;

  std::thread thread;
};

}
