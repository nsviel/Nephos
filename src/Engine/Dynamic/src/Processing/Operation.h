#pragma once

#include <Utility/Specific/Common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Device;}

namespace k4n::structure{class K4N;}
namespace utl::thread{class Pool;}
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
  void start_thread(k4n::dev::Device* sensor);
  void run_thread(k4n::dev::Device* sensor);
  void wait_thread();

  //Subfunction
  void colorize_object(k4n::dev::Device* sensor);
  void voxelize_object(k4n::dev::Device* sensor);
  void triangularize_object(k4n::dev::Device* sensor);
  void update_object(k4n::dev::Device* sensor);

private:
  ope::Voxelizer* ope_voxelizer;
  ope::Triangulation* ope_trianguler;
  ope::color::Colorizer* ope_colorizer;
  ope::attribut::Normal* ope_normal;

  utl::thread::Pool* thread_pool;

  bool idle = true;
};

}
