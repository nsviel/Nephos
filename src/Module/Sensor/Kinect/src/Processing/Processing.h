#pragma once

namespace k4n{class Node;}
namespace k4n::structure{class Sensor;}
namespace k4n::processing::cloud{class Data;}
namespace k4n::processing::image{class Data;}
namespace dyn::image{class Operation;}
namespace dyn::cloud{class Operation;}
namespace utl::thread{class Pool;}


namespace k4n{

class Processing
{
public:
  //Constructor / Destructor
  Processing(k4n::Node* node_k4n);
  ~Processing();

public:
  //Main function
  void start_thread(k4n::structure::Sensor* sensor);
  void run_thread(k4n::structure::Sensor* sensor);
  void wait_thread();

  //Subfunction
  void image_processing(k4n::structure::Sensor* sensor);
  void cloud_processing(k4n::structure::Sensor* sensor);

private:
  k4n::processing::image::Data* k4n_image;
  k4n::processing::cloud::Data* k4n_cloud;
  utl::thread::Pool* thread_pool;
  dyn::image::Operation* dyn_ope_image;
  dyn::cloud::Operation* dyn_ope_cloud;

  bool thread_idle = true;
};

}
