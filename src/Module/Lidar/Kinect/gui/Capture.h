#pragma once

#include <Utility/Specific/Common.h>

namespace gui{class Node;}
namespace k4n{class Node;}
namespace k4n::dev{class Master;}
namespace k4n::utils{class Configuration;}
namespace dat{class Set;}


namespace k4n::gui{

class Capture
{
public:
  //Constructor / Destructor
  Capture(k4n::Node* node_k4n);
  ~Capture();

  //Main function
  void show_list_device(k4n::dev::Master* master);
  void show_info_master(k4n::dev::Master* master);

  //Subfunction
  void configuration_depth(k4n::dev::Master* master);
  void configuration_color(k4n::dev::Master* master);
  void configuration_color_control(k4n::dev::Master* master);
  void configuration_fps(k4n::dev::Master* master);
  void configuration_synchro(k4n::dev::Master* master);
  void configuration_button(k4n::dev::Master* master);

private:
  k4n::Node* node_k4n;
  k4n::utils::Configuration* k4n_config;
  dat::Set* dat_set;

  int item_width;
};

}
