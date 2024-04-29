#pragma once

#include <Utility/Specific/Common.h>

namespace prf{class Node;}
namespace eng{class Node;}
namespace cap{class Node;}
namespace k4n::dev{class Swarm;}
namespace k4n::thread{class Connection;}
namespace k4n::gui{class Player;}
namespace k4n::gui{class Stream;}
namespace k4n::structure{class K4N;}
namespace k4n::thread{class Pool;}
namespace k4n::calibration{class Model;}
namespace rad{class Node;}
namespace ldr{class Node;}


namespace k4n{

class Node : public utl::type::Node
{
public:
  //Constructor / Destructor
  Node(cap::Node* node_capture);
  ~Node();

public:
  //Main function
  void config();
  void init();
  void loop();
  void gui();
  void clean();

  inline eng::Node* get_node_engine(){return node_engine;}
  inline prf::Node* get_node_profiler(){return node_profiler;}
  inline rad::Node* get_node_radio(){return node_radio;}

  inline k4n::dev::Swarm* get_k4n_swarm(){return k4n_swarm;}
  inline k4n::thread::Pool* get_k4n_pool(){return k4n_pool;}
  inline k4n::structure::K4N* get_k4n_struct(){return k4n_struct;}
  inline k4n::gui::Player* get_k4n_gui_player(){return gui_player;}

private:
  //Dependancy
  ldr::Node* node_loader;
  eng::Node* node_engine;
  prf::Node* node_profiler;
  rad::Node* node_radio;

  //Child
  k4n::thread::Pool* k4n_pool;
  k4n::structure::K4N* k4n_struct;
  k4n::dev::Swarm* k4n_swarm;
  k4n::thread::Connection* k4n_connection;
  k4n::gui::Player* gui_player;
  k4n::gui::Stream* gui_stream;
};

}
