#pragma once

#include <Dynamic/src/Base/Radiometry.h>
#include <Utility/Specific/Common.h>

namespace dyn{class Node;}
namespace dyn{class Structure;}
namespace dyn::base{class Sensor;}
namespace utl::thread{class Pool;}


namespace dyn::cloud{

class Radiometry : public dyn::base::Radiometry
{
public:
  //Constructor / Destructor
  Radiometry(dyn::Node* node_dynamic);
  ~Radiometry();

public:
  //Main function
  void start_thread(dyn::base::Sensor* sensor);
  void run_thread(dyn::base::Sensor* sensor);
  void wait_thread();
  
private:
  dyn::Structure* dyn_struct;

  std::thread thread;
  bool thread_idle = true;
};

}
