#pragma once


#include <Engine/Camera/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Element/Namespace.h>

class Engine;

namespace camera::src{
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

  inline camera::src::Control* get_camera_control(){return cam_control;}
  inline camera::src::Manager* get_camera_manager(){return cam_manager;}

private:
  camera::src::Control* cam_control;
  camera::src::Manager* cam_manager;
};

}
