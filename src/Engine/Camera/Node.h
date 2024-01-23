#pragma once


#include <Engine/Camera/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Element/Namespace.h>

class Engine;

namespace eng::camera{
class Control;
class Manager;


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

  inline eng::camera::Control* get_camera_control(){return cam_control;}
  inline eng::camera::Manager* get_camera_manager(){return cam_manager;}

private:
  eng::camera::Control* cam_control;
  eng::camera::Manager* cam_manager;
};

}
