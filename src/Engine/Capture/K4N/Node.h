#pragma once

#include <Utility/Specific/common.h>

namespace prf{class Node;}
namespace eng::capture{class Node;}
namespace eng::scene{class Node;}
namespace k4n::dev{class Swarm;}
namespace k4n::thread{class Connection;}
namespace k4n::gui{class Player;}
namespace k4n::gui{class Stream;}
namespace k4n::gui{class Control;}
namespace k4n::gui{class Matching;}
namespace k4n::structure{class K4N;}
namespace k4n::thread{class Pool;}
namespace k4n::calibration{class Model;}


namespace k4n{

class Node : public utl::type::Node
{
public:
  //Constructor / Destructor
  Node(eng::capture::Node* node_capture);
  ~Node();

public:
  //Main function
  void config();
  void init();
  void loop();
  void gui();
  void control();
  void clean();

  inline eng::scene::Node* get_node_scene(){return node_scene;}
  inline eng::Node* get_node_engine(){return node_engine;}
  inline prf::Node* get_node_profiler(){return node_profiler;}

  inline k4n::dev::Swarm* get_k4n_swarm(){return k4n_swarm;}
  inline k4n::calibration::Model* get_k4n_model(){return k4n_model;}
  inline k4n::thread::Pool* get_k4n_pool(){return k4n_pool;}
  inline k4n::structure::K4N* get_k4n_struct(){return k4n_struct;}

private:
  //Dependancy
  eng::Node* node_engine;
  eng::scene::Node* node_scene;
  prf::Node* node_profiler;

  //Child
  k4n::thread::Pool* k4n_pool;
  k4n::structure::K4N* k4n_struct;
  k4n::dev::Swarm* k4n_swarm;
  k4n::thread::Connection* k4n_connection;
  k4n::calibration::Model* k4n_model;
  k4n::gui::Player* gui_device;
  k4n::gui::Stream* gui_stream;
  k4n::gui::Control* gui_control;
  k4n::gui::Matching* gui_matching;
};

}
