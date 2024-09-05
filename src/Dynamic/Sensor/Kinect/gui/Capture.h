#pragma once

#include <memory>

namespace k4n{class Node;}
namespace k4n{class Structure;}
namespace k4n::capture{class Sensor;}
namespace k4n::capture{class Capture;}
namespace k4n::capture{class Configuration;}


namespace k4n::gui{

class Capture
{
public:
  //Constructor / Destructor
  Capture(k4n::Node* node_k4n);
  ~Capture();

  //Main function
  void show_parameter(k4n::capture::Sensor& sensor);

  //Subfunction
  void show_transformation_mode();
  void show_firmware_info(k4n::capture::Sensor& sensor);
  void configuration_depth();
  void configuration_color();
  void configuration_color_control();
  void configuration_fps();
  void configuration_synchro();
  void configuration_button();

private:
  k4n::Structure* k4n_struct;
  k4n::capture::Capture* k4n_capture;
  k4n::capture::Configuration* k4n_config;

  int item_width;
};

}
