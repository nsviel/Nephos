#pragma once

namespace k4n{class Node;}
namespace k4n::base{class Sensor;}
namespace thr::task{class Pool;}


namespace rad::processing{

class Registration
{
public:
  //Constructor / Destructor
  Registration(k4n::Node* node_k4n);
  ~Registration();

public:
  //Main function
  void start_thread(std::shared_ptr<k4n::base::Sensor> sensor);
  void run_thread(std::shared_ptr<k4n::base::Sensor> sensor);
  void wait_thread();

  //Subfunction


private:
  thr::task::Pool* thread_pool;

  bool idle = true;
};

}
