#pragma once

namespace k4n{class Node;}
namespace k4n::structure{class Sensor;}
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
  void start_thread(k4n::structure::Sensor* sensor);
  void run_thread(k4n::structure::Sensor* sensor);
  void wait_thread();

  //Subfunction


private:
  utl::thread::Pool* thread_pool;

  bool idle = true;
};

}
