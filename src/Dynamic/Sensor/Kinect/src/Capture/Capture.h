#pragma once

#include <memory>
#include <string>

namespace k4n{class Node;}
namespace k4n{class Structure;}
namespace k4n::capture{class Sensor;}


namespace k4n::capture{

class Capture
{
public:
  //Constructor / Destructor
  Capture(k4n::Node* node_k4n);
  ~Capture();

public:
  //Main function
  void init_info(k4n::capture::Sensor& sensor);
  void init_device(k4n::capture::Sensor& sensor);
  void init_capture(k4n::capture::Sensor& sensor);
  void manage_configuration();

private:
  k4n::Structure* k4n_struct;
};

}
