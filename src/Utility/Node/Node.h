#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Element/Namespace.h>

class Config;
class UTL_capture;


namespace utility{

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

  inline util::element::UTL_window* get_utl_window(){return utl_window;}
  inline UTL_capture* get_utl_capture(){return utl_capture;}

private:
  util::element::UTL_window* utl_window;
  UTL_capture* utl_capture;
};

}
