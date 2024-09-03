#pragma once

#include <Utility/Base/Class/Node.h>

namespace app{class Node;}
namespace core{class Node;}
namespace sce{class Init;}


namespace sce{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(app::Node* node_app);
  ~Node();

public:
  void init();

  inline core::Node* get_node_core(){return node_core;}

private:
  //Dependancy
  core::Node* node_core;

  //Child
  sce::Init* sce_init;
};

}
