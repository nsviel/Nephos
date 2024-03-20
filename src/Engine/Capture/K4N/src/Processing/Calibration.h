#pragma once

#include <Utility/Specific/common.h>

namespace k4n{class Node;}
namespace k4n::structure{class Struct_k4n;}
namespace k4n::dev{class Sensor;}
namespace k4n::thread{class Pool;}
namespace eng::scene{class Exporter;}
namespace format::ply{class Exporter;}


namespace k4n::processing{

class Calibration
{
public:
  //Constructor / Destructor
  Calibration(k4n::Node* node_k4n);
  ~Calibration();

public:
  //Main function
  void start_thread(k4n::dev::Sensor* sensor);
  void run_thread(k4n::dev::Sensor* sensor);
  void wait_thread();

  //Subfunction


private:
  k4n::thread::Pool* thread_pool;
  k4n::structure::Struct_k4n* struct_k4n;

  bool idle = true;
};

}
