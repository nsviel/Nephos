#pragma once

#include <Utility/Specific/Common.h>

namespace eng{class Node;}
namespace vld{class Node;}
namespace vld::processing{class Velodyne;}
namespace vld::structure{class Main;}
namespace vld::gui{class Player;}
namespace vld::gui{class Server;}


namespace vld::gui{

class Velodyne
{
public:
  //Constructor / Destructor
  Velodyne(vld::structure::Main* vld_struct, bool* show_window);
  ~Velodyne();

public:
  //Main function
  void run_panel();
  void design_panel();

private:
  vld::structure::Main* vld_struct;
  vld::gui::Player* gui_player;
  vld::gui::Server* gui_server;

  bool* show_window;
  std::string name;
  std::string open_tab = "";
};

}
