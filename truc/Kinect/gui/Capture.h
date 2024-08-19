#pragma once

namespace gui{class Node;}
namespace k4n{class Node;}
namespace k4n{class Structure;}
namespace k4n::base{class Sensor;}
namespace k4n::capture{class Configuration;}
namespace dat::elm{class Set;}
namespace dat::base{class Set;}


namespace k4n::gui{

class Capture
{
public:
  //Constructor / Destructor
  Capture(k4n::Node* node_k4n);
  ~Capture();

  //Main function
  void show_parameter(dat::base::Set* set);

  //Subfunction
  void show_list_device(dat::base::Set* set);
  void show_transformation_mode(dat::base::Set* set);
  void show_firmware_info(k4n::base::Sensor* sensor);
  void configuration_depth(dat::base::Set* set);
  void configuration_color(dat::base::Set* set);
  void configuration_color_control(dat::base::Set* set);
  void configuration_fps(dat::base::Set* set);
  void configuration_synchro(dat::base::Set* set);
  void configuration_button(dat::base::Set* set);

private:
  k4n::Structure* k4n_struct;
  k4n::capture::Configuration* k4n_config;
  dat::elm::Set* dat_set;

  int item_width;
};

}
