#pragma once

#include <memory>

namespace gui{class Node;}
namespace k4n{class Node;}
namespace k4n{class Structure;}
namespace k4n::base{class Sensor;}
namespace dat::elm{class Set;}
namespace dat::base{class Set;}


namespace k4n::gui{

class Device
{
public:
  //Constructor / Destructor
  Device(k4n::Node* node_k4n);
  ~Device();

  //Main function
  void show_parameter(std::shared_ptr<dat::base::Set> set);

  //Subfunction
  void show_list_device(std::shared_ptr<dat::base::Set> set);

private:
  k4n::Structure* k4n_struct;
  dat::elm::Set* dat_set;

  int item_width;
};

}
