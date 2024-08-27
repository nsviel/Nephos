#pragma once

#include <Utility/Base/Class/Node.h>

namespace dyn{class Node;}
namespace core{class Node;}
namespace dat{class Node;}
namespace core{class Node;}
namespace rad{class Node;}
namespace prf{class Node;}

namespace dyn::prc{class Structure;}
namespace dyn::prc::cloud{class Operation;}
namespace dyn::prc::image{class Operation;}


namespace dyn::prc{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(dyn::Node* node_dynamic);
  ~Node();

public:
  //Main function
  void loop();
  void reset();

  inline core::Node* get_node_core(){return node_core;}
  inline dat::Node* get_node_data(){return node_data;}
  inline rad::Node* get_node_radio(){return node_radio;}
  inline prf::Node* get_node_profiler(){return node_profiler;}

  inline dyn::prc::Structure* get_dyn_struct(){return dyn_struct;}
  inline dyn::prc::cloud::Operation* get_ope_cloud(){return dyn_ope_cloud;}
  inline dyn::prc::image::Operation* get_ope_image(){return dyn_ope_image;}

private:
  core::Node* node_core;
  dat::Node* node_data;
  rad::Node* node_radio;
  prf::Node* node_profiler;

  dyn::prc::Structure* dyn_struct;
  dyn::prc::cloud::Operation* dyn_ope_cloud;
  dyn::prc::image::Operation* dyn_ope_image;
};

}
