#pragma once

#include <Utility/Specific/Common.h>

namespace gui{class Node;}
namespace vk{class Node;}
namespace eng{class Node;}
namespace engine = eng;


namespace gui::tab::eng{

class Menu
{
public:
  //Constructor / Destructor
  Menu(gui::Node* node_gui);
  ~Menu();

public:
  //Main functions
  void draw();

  //Subfunction
  void menu_panel();
  void menu_loader();
  void menu_screenshot();

private:
  gui::Node* node_gui;
  engine::Node* node_engine;
  vk::Node* node_vulkan;
};

}
