#pragma once

#include <Utility/Specific/common.h>

namespace prf{class Node;}
namespace eng::capture{class Node;}
namespace eng::scene{class Node;}
namespace k4n::dev{class Swarm;}
namespace k4n::dev{class Connection;}
namespace k4n::gui{class Player;}
namespace k4n::gui{class Stream;}
namespace k4n::gui{class Control;}


namespace k4n{

class Node : public utl::type::Node
{
public:
  //Constructor / Destructor
  Node(eng::capture::Node* node_capture);
  ~Node();

public:
  //Main function
  void init();
  void loop();
  void gui();
  void control();
  void exit();

  inline eng::scene::Node* get_node_scene(){return node_scene;}
  inline eng::Node* get_node_engine(){return node_engine;}
  inline prf::Node* get_node_profiler(){return node_profiler;}

  inline k4n::dev::Swarm* get_k4n_swarm(){return k4n_swarm;}

private:
  //Dependancy
  eng::Node* node_engine;
  eng::scene::Node* node_scene;
  prf::Node* node_profiler;

  //Child
  k4n::dev::Swarm* k4n_swarm;
  k4n::dev::Connection* k4n_connection;
  k4n::gui::Player* gui_device;
  k4n::gui::Stream* gui_stream;
  k4n::gui::Control* gui_control;
};

}
