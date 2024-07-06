#pragma once

namespace k4n{class Node;}
namespace k4n{class Structure;}
namespace k4n::structure{class Sensor;}
namespace k4n::processing{class Cloud;}
namespace utl::thread{class Pool;}
namespace dyn::image{class Operation;}
namespace k4n::processing::image{class Transformation;}
namespace k4n::processing::image{class Color;}
namespace k4n::processing::image{class Depth;}
namespace k4n::processing::image{class Infrared;}


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
  void find_data_from_capture(k4n::structure::Sensor* device);
  void find_data_cloud(k4n::structure::Sensor* sensor);

private:
  k4n::Structure* k4n_struct;
  k4n::processing::Cloud* k4n_cloud;
  utl::thread::Pool* thread_pool;
  dyn::image::Operation* dyn_operation;
  k4n::processing::image::Transformation* k4n_transformation;
  k4n::processing::image::Color* k4n_color;
  k4n::processing::image::Depth* k4n_depth;
  k4n::processing::image::Infrared* k4n_ir;

  bool thread_idle = true;
};

}
