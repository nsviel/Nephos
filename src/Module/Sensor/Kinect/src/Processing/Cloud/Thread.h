#pragma once

namespace k4n{class Node;}
namespace k4n::structure{class Sensor;}
namespace k4n::processing::cloud{class Data;}
namespace utl::thread{class Pool;}
namespace dyn::cloud{class Operation;}


namespace k4n::processing::cloud{

class Thread
{
public:
  //Constructor / Destructor
  Thread(k4n::Node* node_k4n);
  ~Thread();

public:
  //Main function
  void start_thread(k4n::structure::Sensor* sensor);
  void run_thread(k4n::structure::Sensor* sensor);
  void wait_thread();

  //Subfunction
  void extract_data(k4n::structure::Sensor* device);
  void run_operation(k4n::structure::Sensor* sensor);

private:
  k4n::processing::cloud::Data* k4n_data;
  utl::thread::Pool* thread_pool;
  dyn::cloud::Operation* dyn_operation;

  bool thread_idle = true;
};

}
