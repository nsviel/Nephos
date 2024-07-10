#pragma once

#include <Utility/Base/Class/Node.h>

namespace eng{class Node;}
namespace dat{class Node;}
namespace eng{class Node;}
namespace rad{class Node;}
namespace prf{class Node;}
namespace dyn{class Structure;}
namespace dyn::player{class Player;}
namespace dyn::element{class Sensor;}
namespace dyn::cloud{class Operation;}
namespace dyn::image{class Operation;}
namespace dyn::gui{class Panel;}
namespace dyn::gui{class Stream;}


namespace dyn{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* node_engine);
  ~Node();

public:
  void loop();
  void gui();
  void reset();

  inline eng::Node* get_node_engine(){return node_engine;}
  inline dat::Node* get_node_data(){return node_data;}
  inline rad::Node* get_node_radio(){return node_radio;}
  inline prf::Node* get_node_profiler(){return node_profiler;}

  inline dyn::Structure* get_dyn_struct(){return dyn_struct;}
  inline dyn::player::Player* get_dyn_player(){return dyn_player;}
  inline dyn::element::Sensor* get_dyn_sensor(){return dyn_sensor;}
  inline dyn::cloud::Operation* get_ope_cloud(){return dyn_ope_cloud;}
  inline dyn::image::Operation* get_ope_image(){return dyn_ope_image;}
  inline dyn::gui::Panel* get_gui_player(){return gui_player;}

private:
  eng::Node* node_engine;
  dat::Node* node_data;
  rad::Node* node_radio;
  prf::Node* node_profiler;

  dyn::Structure* dyn_struct;
  dyn::player::Player* dyn_player;
  dyn::element::Sensor* dyn_sensor;
  dyn::cloud::Operation* dyn_ope_cloud;
  dyn::image::Operation* dyn_ope_image;
  dyn::gui::Panel* gui_player;
  dyn::gui::Stream* gui_stream;
};

}
