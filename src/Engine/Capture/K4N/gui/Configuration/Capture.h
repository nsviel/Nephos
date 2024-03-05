#pragma once

#include <Utility/Specific/common.h>

namespace gui{class Node;}
namespace k4n{class Node;}
namespace k4n::dev{class Master;}
namespace k4n::dev{class Swarm;}
namespace eng::scene{class Set;}


namespace k4n::gui{

class Capture
{
public:
  //Constructor / Destructor
  Capture(k4n::Node* node_k4n);
  ~Capture();

  //Main function
  void show_master_capture(k4n::dev::Master* master);

  //Subfunction
  void list_device(k4n::dev::Master* master);
  void configuration_depth(k4n::dev::Master* master);
  void configuration_color(k4n::dev::Master* master);
  void configuration_device(k4n::dev::Master* master);
  void firmware_info(k4n::dev::Master* master);

private:
  k4n::Node* node_k4n;
  k4n::dev::Swarm* k4n_swarm;
  eng::scene::Set* sce_set;

  int item_width;
};

}
