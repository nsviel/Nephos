#ifndef CAMERA_H
#define CAMERA_H

#include "struct_camera.h"

#include <ELE_specific/common.h>

class Engine;
class Param;
class CAM_arcball;
class CAM_first_person;
class CAM_zoom;
class CAM_proj;


class Camera
{
public:
  Camera(Engine* engine);
  ~Camera();

public:
  //Main function
  void control(string what, bool fast);
  void loop_cam_mouse();
  void reset();

  //MVP matrices
  mat4 compute_cam_view();
  void compute_cam_mvp(Object* object);
  mat4 compute_cam_proj();
  mat4 compute_cam_mvp();

  //Camera mode
  void set_mode_projection(int value);
  void set_mode_angle(int value);
  void set_mode_view(int value);

  //Specific function
  mat4 compute_cam_world_pose();
  void compute_zoom(float value);

  inline mat4 get_cam_view(){return compute_cam_view();}
  inline mat4 get_cam_proj(){return compute_cam_proj();}
  inline mat4 get_mvpMatrix(){return compute_cam_mvp();}

private:
  Engine* engine;
  Param* param;
  CAM_arcball* cam_arcball;
  CAM_first_person* cam_fp;
  CAM_zoom* cam_zoom;
  CAM_proj* cam_proj;

  vec3 arcball_origin;
};

#endif
