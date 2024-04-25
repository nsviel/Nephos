#pragma once

#include <Utility/Specific/Common.h>

namespace k4n{class Node;}
namespace k4n::structure{class K4N;}
namespace k4n::dev{class Sensor;}
namespace k4n::thread{class Pool;}
namespace k4n::detection{class Detector;}


namespace k4n::processing{

class Detection
{
public:
  //Constructor / Destructor
  Detection(k4n::Node* node_k4n);
  ~Detection();

public:
  //Main function
  void start_thread(k4n::dev::Sensor* sensor);
  void run_thread(k4n::dev::Sensor* sensor);
  void wait_thread();

  //Subfunction
  void make_detection(k4n::dev::Sensor* sensor);

private:
  k4n::thread::Pool* k4n_pool;
  k4n::structure::K4N* k4n_struct;
  k4n::detection::Detector* k4n_detector;

  bool idle = true;
};

}
