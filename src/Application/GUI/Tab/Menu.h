#pragma once

#include <string>

namespace gui{class Node;}
namespace cam{class Manager;}


namespace gui::tab::eng{

class Menu
{
public:
  //Constructor / Destructor
  Menu(gui::Node* node_gui);
  ~Menu();

public:
  //Main function
  void draw();

  //Subfunction
  void menu_panel();
  void menu_shortcut(std::string name);
  void menu_screenshot();

private:
  gui::Node* node_gui;
  cam::Manager* cam_manager;
};

}
