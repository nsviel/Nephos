#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Element/Namespace.h>

class Config;
class UTL_capture;


namespace util{

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

  inline util::element::Window* get_utl_window(){return utl_window;}
  inline UTL_capture* get_utl_capture(){return utl_capture;}

private:
  util::element::Window* utl_window;
  UTL_capture* utl_capture;
};

}
