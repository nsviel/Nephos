#pragma once

#include <string>

namespace vld{class Node;}
namespace vld{class Structure;}
namespace vld::processing{class Velodyne;}
namespace vld::gui{class Player;}
namespace vld::gui{class Server;}


namespace vld::gui{

class Panel
{
public:
  //Constructor / Destructor
  Panel(vld::Node* node_velodyne, bool* show_window);
  ~Panel();

public:
  //Main function
  void run_panel();
  void design_panel();

private:
  vld::Structure* vld_struct;
  vld::gui::Player* gui_player;
  vld::gui::Server* gui_server;

  std::string name;
  std::string open_tab = "";
  bool* show_window;
};

}
