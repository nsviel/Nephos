#pragma once

#include <Utility/UTL_specific/common.h>

class Config;
class UTL_window;
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

  inline UTL_window* get_utl_window(){return utl_window;}
  inline UTL_capture* get_utl_capture(){return utl_capture;}

private:
  UTL_window* utl_window;
  UTL_capture* utl_capture;
};

}
