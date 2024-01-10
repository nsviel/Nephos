#pragma once

#include <Engine/Base/Namespace.h>
#include <Engine/Camera/Namespace.h>
#include <Engine/Camera/Mode/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Element/Namespace.h>

class Engine;

namespace eng::camera{
class Control;


class Node
{
public:
  Node(Engine* engine);
  ~Node();

public:
  //Main function
  void loop();
  void reset();

  inline eng::data::Camera* get_camera(){return camera;};
  inline eng::camera::Control* get_camera_control(){return cam_control;}

private:
  eng::camera::Control* cam_control;
  eng::data::Camera* camera;
};

}
