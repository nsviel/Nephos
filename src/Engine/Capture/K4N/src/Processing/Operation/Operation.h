#pragma once

#include <Utility/Specific/common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Sensor;}
namespace k4n::utils{class Operation;}
namespace k4n::processing{class Recorder;}
namespace k4n::structure{class K4N;}
namespace k4n::thread{class Pool;}
namespace ope{class Voxelizer;}
namespace ope{class Triangulation;}
namespace ope::color{class Colorizer;}
namespace ope::attribut{class Normal;}


namespace k4n::processing{

class Operation
{
public:
  //Constructor / Destructor
  Operation(k4n::Node* node_k4n);
  ~Operation();

public:
  //Main function
  void start_thread(k4n::dev::Sensor* sensor);
  void run_thread(k4n::dev::Sensor* sensor);
  void wait_thread();

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
  k4n::utils::Operation* k4n_operation;
  k4n::processing::Recorder* k4n_recorder;
  k4n::thread::Pool* k4n_pool;

  bool idle = true;
};

}