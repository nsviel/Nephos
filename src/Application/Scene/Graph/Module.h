#pragma once

#include <Utility/Base/Type/Node.h>

namespace sce{class Node;}
namespace k4n{class Node;}


namespace sce{

class Module : public utl::type::Node
{
public:
  //Constructor / Destructor
  Module(sce::Node* node_scene);
  ~Module();

public:
  //Main function
  void init();
  void loop();
  void clean();
  void gui();

private:
  k4n::Node* node_kinect;

};

}
