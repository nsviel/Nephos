#pragma once

#include <glm/glm.hpp>
#include <string>

namespace cam{class Node;}
namespace cam{class Control;}
namespace cam{class Manager;}
namespace cam{class Structure;}


namespace cam::gui{

class Panel
{
public:
  //Constructor / Destructor
  Panel(cam::Node* node_camera, bool* show_window);
  ~Panel();

  //Main function
  void run_panel();
  void design_panel();

  //Sub functions
  void cam_parameter();
  void cam_info();
  void cam_mode();

private:
  cam::Control* cam_control;
  cam::Manager* cam_manager;
  cam::Structure* cam_struct;

  std::string name;
  int item_width;
  bool* show_window;
};

}
