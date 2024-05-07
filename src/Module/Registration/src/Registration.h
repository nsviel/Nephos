#pragma once

#include <Utility/Specific/Common.h>

namespace k4n{class Node;}
namespace k4n::structure{class K4N;}
namespace k4n::dev{class Device;}
namespace utl::thread{class Pool;}


namespace rad::processing{

class Registration
{
public:
  //Constructor / Destructor
  Registration(k4n::Node* node_k4n);
  ~Registration();

public:
  //Main function
  void start_thread(k4n::dev::Device* sensor);
  void run_thread(k4n::dev::Device* sensor);
  void wait_thread();

  //Subfunction


private:
  utl::thread::Pool* thread_pool;
  k4n::structure::K4N* k4n_struct;

  bool idle = true;
};

}
