#pragma once

namespace k4n{class Node;}
namespace k4n::structure{class Sensor;}
namespace k4n::processing::cloud{class Thread;}
namespace k4n::processing::image{class Thread;}
namespace utl::thread{class Pool;}


namespace k4n{

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

private:
  k4n::processing::image::Thread* k4n_image;
  k4n::processing::cloud::Thread* k4n_cloud;
  utl::thread::Pool* thread_pool;

  bool thread_idle = true;
};

}
