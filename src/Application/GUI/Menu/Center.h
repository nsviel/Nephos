#pragma once

#include <string>

namespace gui{class Node;}
namespace cam{class Manager;}
namespace vk::interface{class Render;}


namespace gui::menu{

class Center
{
public:
  //Constructor / Destructor
  Center(gui::Node* node_gui);
  ~Center();

public:
  //Main function
  void draw();

  //Subfunction
  void menu_panel();
  void menu_shortcut(std::string name);
  void menu_screenshot();
  void menu_reload();

private:
  gui::Node* node_gui;
  cam::Manager* cam_manager;
  vk::interface::Render* vk_render;
};

}
