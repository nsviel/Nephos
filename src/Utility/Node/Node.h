#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Element/Namespace.h>
#include <Utility/Capture/Node/Namespace.h>

class Config;


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
  inline util::capture::Node* get_utl_capture(){return utl_capture;}

private:
  util::element::Window* utl_window;
  util::capture::Node* utl_capture;
};

}
