#pragma once

#include <Utility/Specific/Common.h>

#include <glm/glm.hpp>
#include <string>
#include <list>

enum camera_mode{
  CAMERA_MODE_PLAYER = 0,
  CAMERA_MODE_ARCBALL = 1,
};

enum camera_projection{
  CAMERA_PROJ_PERSPECTIVE = 0,
  CAMERA_PROJ_ORTHOGRAPHIC = 1,
};

enum camera_direction{
  CAMERA_FORWARD = 0,
  CAMERA_BACKWARD = 1,
  CAMERA_RIGHT = 2,
  CAMERA_LEFT = 3,
  CAMERA_UP = 4,
  CAMERA_DOWN = 5,
};

namespace utl::entity{
class Glyph;


class Camera : public utl::type::Entity
{
public:
  //Constructor / Destructor
  Camera();
  ~Camera();

  //Main function
  void update_pose();
  void reset_entity();

public:
  //Camera pose
  glm::vec3 cam_F = glm::vec3(0.0f); // Front
  glm::vec3 cam_R = glm::vec3(0.0f); // Right
  glm::vec3 cam_U = glm::vec3(0.0f); // Up
  glm::vec3 cam_P = glm::vec3(0.0f); // Pose
  glm::vec3 cam_COM = glm::vec3(0.0f);
  float angle_azimuth = 0;
  float angle_elevation = 0;
  bool cam_move = false;
  bool cam_pose = false;

  //Camera paramater
  float fov = 0;
  float velocity = 0;
  float zoom = 0;
  float clip_near = 0;
  float clip_far = 0;
  glm::vec2 panel_center = glm::vec2(0, 0);
  glm::vec2 player_mouse_sensibility = glm::vec2(0, 0);
  glm::vec2 arcball_mouse_sensibility = glm::vec2(0, 0);
  int projection = 0;
  int mode = 0;

  //Camera matrix
  glm::mat4 mat_pose = glm::mat4(1);
  glm::mat4 mat_proj = glm::mat4(1);
  glm::mat4 mat_view = glm::mat4(1);
  glm::mat4 mat_vp = glm::mat4(1);
};


}
