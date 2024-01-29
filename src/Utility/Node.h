#pragma once

#include <Utility/Specific/common.h>

class Config;
namespace utl::element{class Window;}


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
  void gui();
  void exit();

  inline utl::element::Window* get_utl_window(){return utl_window;}

private:
  utl::element::Window* utl_window;
};

}
