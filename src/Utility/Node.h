#pragma once

#include <Utility/Specific/common.h>

class App_main;
namespace prf{class Node;}
namespace utl::element{class Window;}


namespace utl{

class Node : public utl::type::Node
{
public:
  //Constructor / Destructor
  Node(App_main* node_app);
  ~Node();

public:
  //Main function
  void init();
  void loop();
  void gui();
  void exit();

  inline utl::element::Window* get_utl_window(){return utl_window;}
  inline prf::Node* get_node_profiler(){return node_profiler;}

private:
  prf::Node* node_profiler;
  utl::element::Window* utl_window;
};

}
