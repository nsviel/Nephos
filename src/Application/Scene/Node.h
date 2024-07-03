#pragma once

#include <Utility/Base/Class/Node.h>

namespace app{class Node;}
namespace eng{class Node;}
namespace sce{class Init;}
namespace k4n{class Node;}


namespace sce{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(app::Node* node_app);
  ~Node();

public:
  void init();
  void loop();
  void clean();
  void gui();
  void reset();

  inline eng::Node* get_node_engine(){return node_engine;}

private:
  //Dependancy
  eng::Node* node_engine;
  k4n::Node* node_kinect;

  //Child
  sce::Init* sce_init;

  bool show_scene = true;
  bool show_loader = true;
};

}
