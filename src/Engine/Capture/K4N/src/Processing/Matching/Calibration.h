#pragma once

#include <Utility/Specific/Common.h>

namespace k4n{class Node;}
namespace k4n::structure{class K4N;}
namespace k4n::dev{class Sensor;}
namespace k4n::thread{class Pool;}
namespace k4n::calibration{class Calibration;}


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
  k4n::thread::Pool* k4n_pool;
  k4n::structure::K4N* k4n_struct;
  k4n::calibration::Calibration* k4n_calibration;

  bool idle = true;
};

}
