#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Element/src/Namespace.h>

class Config;


namespace utl{

class Node
{
public:
  //Constructor / Destructor
  Node(Config* config);
  ~Node();

public:
  //Main function
  void init();
  void loop();
  void exit();

  inline utl::element::Window* get_utl_window(){return utl_window;}

private:
  utl::element::Window* utl_window;
};

}
