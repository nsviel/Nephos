#pragma once

#include <memory>
#include <thread>

namespace rlx{class Node;}


namespace rlx{

class Factory
{
public:
  //Constructor / Destructor
  Factory(rlx::Node* node_realsense);
  ~Factory();

public:
  //Main function
  std::shared_ptr<rlx::capture::Sensor> create_capture_sensor();

  //Subfunction
  void insert_in_set(rlx::base::Sensor& sensor);
  
private:
};

}
