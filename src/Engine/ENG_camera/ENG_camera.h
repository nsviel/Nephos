#ifndef CAMERA_H
#define CAMERA_H

#include "Struct_camera.h"
#include <ELE_specific/common.h>

class Engine;
class CAM_arcball;
class CAM_first_person;
class CAM_zoom;
class CAM_proj;
class Struct_camera;


class ENG_camera
{
public:
  ENG_camera(Engine* engine);
  ~ENG_camera();

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
  inline Struct_camera* get_camera(){return camera;};

private:
  Engine* engine;
  CAM_arcball* cam_arcball;
  CAM_first_person* cam_fp;
  CAM_zoom* cam_zoom;
  CAM_proj* cam_proj;

  Struct_camera* camera;
  vec3 arcball_origin;
};

#endif
