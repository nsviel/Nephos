#pragma once

namespace k4n{class Node;}
namespace k4n::structure{class Sensor;}
namespace k4n::processing{class Cloud;}
namespace k4n::processing::image{class Data;}
namespace utl::thread{class Pool;}
namespace dyn::image{class Operation;}


namespace k4n::processing::image{

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

private:
  k4n::processing::Cloud* k4n_cloud;
  k4n::processing::image::Data* k4n_data;
  utl::thread::Pool* thread_pool;
  dyn::image::Operation* dyn_operation;

  bool thread_idle = true;
};

}
