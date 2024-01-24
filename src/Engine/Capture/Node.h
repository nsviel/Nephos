#pragma once

#include <Utility/Specific/common.h>

class Engine;
namespace eng::k4n{class Node;}


namespace eng::capture{

class Node
{
public:
  //Constructor / Destructor
  Node(Engine* engine);
  ~Node();

public:
  //Main function
  void init();
  void loop();
  void gui();

  //inline eng::k4n::Node* get_k4n_node(){return k4n_node;}

private:
  eng::k4n::Node* k4n_node;
};

}
