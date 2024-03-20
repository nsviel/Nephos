#pragma once

#include <Utility/Specific/common.h>

namespace gui{class Node;}
namespace k4n{class Node;}
namespace k4n::dev{class Master;}
namespace k4n::dev{class Swarm;}
namespace k4n::config{class Configuration;}
namespace k4n::structure{class K4N;}
namespace eng::scene{class Set;}


namespace k4n::gui{

class Capture
{
public:
  //Constructor / Destructor
  Capture(k4n::Node* node_k4n);
  ~Capture();

  //Main function
  void list_device(k4n::dev::Master* master);
  void show_master_capture(k4n::dev::Master* master);

  //Subfunction
  void configuration_depth(k4n::dev::Master* master);
  void configuration_color(k4n::dev::Master* master);
  void configuration_color_control(k4n::dev::Master* master);
  void configuration_fps(k4n::dev::Master* master);
  void configuration_synchro(k4n::dev::Master* master);
  void configuration_button(k4n::dev::Master* master);

private:
  k4n::Node* node_k4n;
  k4n::dev::Swarm* k4n_swarm;
  k4n::config::Configuration* k4n_config;
  k4n::structure::K4N* k4n_struct;
  eng::scene::Set* sce_set;

  int item_width;
};

}
