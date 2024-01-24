#pragma once

#include <Utility/Specific/common.h>

class Engine;
namespace eng::k4n::dev{class Swarm;}
namespace eng::k4n::dev{class Connection;}
namespace eng::k4n::gui{class Device;}
namespace eng::k4n::gui{class Stream;}


namespace eng::k4n{

class Node
{
public:
  //Constructor / Destructor
  Node(Engine* engine);
  ~Node();

public:
  //Main function
  void init();
  void loop();
  void gui();

  inline Engine* get_engine(){return engine;}
  inline eng::k4n::dev::Swarm* get_k4n_swarm(){return k4n_swarm;}

private:
  Engine* engine;
  eng::k4n::dev::Swarm* k4n_swarm;
  eng::k4n::dev::Connection* k4n_connection;
  eng::k4n::gui::Device* gui_device;
  eng::k4n::gui::Stream* gui_stream;

  bool show_gui = true;
};

}
