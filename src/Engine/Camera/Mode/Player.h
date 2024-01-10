#pragma once

#include <Engine/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Element/Namespace.h>


namespace eng::camera::mode{

class Player
{
public:
  Player(util::element::Window* utl_window);
  ~Player();

public:
  mat4 fp_view_mat(eng::data::Camera* camera);
  void fp_cam_mouse(eng::data::Camera* camera);

private:
  util::element::Window* utl_window;

  vec2 mouse_pose_old;
};

}
