#pragma once

#include <Engine/Base/Struct_entity.h>

#include <glm/glm.hpp>
#include <string>


namespace eng::data{

enum camera_mode{
  CAMERA_MODE_PLAYER = 0,
  CAMERA_MODE_ARCBALL = 1,
};

struct Camera : public eng::data::Entity
{
  //---------------------------

  Camera();
  void reset();

  glm::vec2 pos = glm::vec2(0.0f);
  glm::vec2 dim = glm::vec2(0.0f);

  glm::vec3 cam_F = glm::vec3(0.0f); // Front
  glm::vec3 cam_R = glm::vec3(0.0f); // Right
  glm::vec3 cam_U = glm::vec3(0.0f); // Up
  glm::vec3 cam_P = glm::vec3(0.0f); // Pose
  glm::vec3 cam_COM = glm::vec3(0.0f);
  glm::vec3 cam_COM_obj = glm::vec3(0.0f);

  float angle_azimuth;
  float angle_elevation;

  float fov = 0;
  float speed_mouse;
  float speed_move;
  float zoom = 0;
  float clip_near;
  float clip_far;

  std::string projection;
  std::string mode;

  bool cam_move = false;
  bool cam_pose = false;
  glm::mat4 cam_pose_mat = glm::mat4(1);
  glm::mat4 mat_proj = glm::mat4(1);
  glm::mat4 mat_view = glm::mat4(1);
  glm::mat4 mat_vp = glm::mat4(1);

  //---------------------------
};

}
