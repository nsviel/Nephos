#pragma once

namespace k4n{class Node;}
namespace k4n::structure{class Sensor;}
namespace k4n::processing::image{class Transformation;}
namespace k4n::processing::image{class Color;}
namespace k4n::processing::image{class Depth;}
namespace k4n::processing::image{class Infrared;}
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

  //Subfunction
  void extract_data(k4n::structure::Sensor* device);
  void run_operation(k4n::structure::Sensor* sensor);

private:
  k4n::processing::image::Transformation* k4n_transformation;
  k4n::processing::image::Color* k4n_color;
  k4n::processing::image::Depth* k4n_depth;
  k4n::processing::image::Infrared* k4n_ir;
  utl::thread::Pool* thread_pool;
  dyn::image::Operation* dyn_operation;

  bool thread_idle = true;
};

}
