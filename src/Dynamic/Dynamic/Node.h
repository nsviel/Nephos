#pragma once

#include <Utility/Base/Class/Node.h>

namespace core{class Node;}
namespace dat{class Node;}
namespace core{class Node;}
namespace rad{class Node;}
namespace prf{class Node;}
namespace ope{class Node;}

namespace dyn{class Structure;}
namespace dyn::element{class Sensor;}
namespace dyn::cloud{class Operation;}
namespace dyn::image{class Operation;}


namespace dyn{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(core::Node* node_core);
  ~Node();

public:
  void loop();
  void gui();
  void reset();

  inline core::Node* get_node_core(){return node_core;}
  inline dat::Node* get_node_data(){return node_data;}
  inline rad::Node* get_node_radio(){return node_radio;}
  inline prf::Node* get_node_profiler(){return node_profiler;}
  inline ope::Node* get_node_operation(){return node_operation;}

  inline dyn::Structure* get_dyn_struct(){return dyn_struct;}
  inline dyn::element::Sensor* get_dyn_sensor(){return dyn_sensor;}
  inline dyn::cloud::Operation* get_ope_cloud(){return dyn_ope_cloud;}
  inline dyn::image::Operation* get_ope_image(){return dyn_ope_image;}

private:
  core::Node* node_core;
  dat::Node* node_data;
  rad::Node* node_radio;
  prf::Node* node_profiler;
  ope::Node* node_operation;

  dyn::Structure* dyn_struct;
  dyn::element::Sensor* dyn_sensor;
  dyn::cloud::Operation* dyn_ope_cloud;
  dyn::image::Operation* dyn_ope_image;
};

}
