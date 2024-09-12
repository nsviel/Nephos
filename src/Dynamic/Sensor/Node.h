#pragma once

#include <Utility/Base/Class/Node.h>

namespace dyn{class Node;}
namespace dyn::prc{class Node;}
namespace core{class Node;}

namespace k4n{class Node;}
namespace rlx{class Node;}
namespace vld{class Node;}


namespace dyn::sen{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(dyn::Node* node_dynamic);
  ~Node();

public:
  //Main function
  void init();
  void clean();

  inline core::Node* get_node_core(){return node_core;}
  inline dyn::prc::Node* get_node_processing(){return node_processing;}

private:
  core::Node* node_core;
  dyn::prc::Node* node_processing;

  k4n::Node* node_kinect;
  rlx::Node* node_realsense;
  vld::Node* node_velodyne;
};

}
