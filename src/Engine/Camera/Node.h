#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Element/src/Namespace.h>

class Engine;
namespace eng::cam{class Control;}
namespace eng::cam{class Manager;}


namespace eng::cam{

class Node
{
public:
  Node(Engine* engine);
  ~Node();

public:
  //Main function
  void init();
  void loop();
  void reset();

  inline utl::element::Window* get_utl_window(){return utl_window;}
  inline eng::cam::Control* get_camera_control(){return cam_control;}
  inline eng::cam::Manager* get_camera_manager(){return cam_manager;}

private:
  utl::element::Window* utl_window;
  eng::cam::Control* cam_control;
  eng::cam::Manager* cam_manager;
};

}
