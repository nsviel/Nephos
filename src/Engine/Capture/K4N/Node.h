#pragma once

#include <Utility/Specific/common.h>

namespace eng{class Node;}
namespace eng::k4n::dev{class Swarm;}
namespace eng::k4n::dev{class Connection;}
namespace eng::k4n::gui{class Device;}
namespace eng::k4n::gui{class Stream;}
namespace eng::k4n::gui{class Control;}


namespace eng::k4n{

class Node : public utl::type::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* engine);
  ~Node();

public:
  //Main function
  void init();
  void loop();
  void gui();
  void control();

  inline eng::Node* get_node_engine(){return engine;}
  inline eng::k4n::dev::Swarm* get_k4n_swarm(){return k4n_swarm;}

private:
  eng::Node* engine;
  eng::k4n::dev::Swarm* k4n_swarm;
  eng::k4n::dev::Connection* k4n_connection;
  eng::k4n::gui::Device* gui_device;
  eng::k4n::gui::Stream* gui_stream;
  eng::k4n::gui::Control* gui_control;
};

}
