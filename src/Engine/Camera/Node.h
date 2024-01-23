#pragma once


#include <Engine/Camera/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Element/src/Namespace.h>

class Engine;

namespace eng::cam{
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

  inline eng::cam::Control* get_camera_control(){return cam_control;}
  inline eng::cam::Manager* get_camera_manager(){return cam_manager;}

private:
  eng::cam::Control* cam_control;
  eng::cam::Manager* cam_manager;
};

}
