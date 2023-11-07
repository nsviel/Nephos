#include "ENG_camera.h"
#include "Mode/CAM_first_person.h"
#include "Mode/CAM_arcball.h"
#include "Projection/CAM_zoom.h"
#include "Projection/CAM_proj.h"

#include <Engine.h>
#include <Param.h>


//Constructor / Destructor
ENG_camera::ENG_camera(Engine* engine){
  //---------------------------

  this->param = engine->get_param();
  this->cam_arcball = new CAM_arcball(engine->get_ele_window());
  this->cam_fp = new CAM_first_person(engine->get_ele_window());
  this->cam_zoom = new CAM_zoom(engine->get_ele_window());
  this->cam_proj = new CAM_proj(engine->get_ele_window());

  this->arcball_origin = vec3(0, 0, 0);

  //---------------------------
}
ENG_camera::~ENG_camera(){
  //---------------------------

  delete cam_arcball;
  delete cam_fp;
  delete cam_zoom;
  delete cam_proj;

  //---------------------------
}

//Main function
void ENG_camera::control(string what, bool fast){
  Struct_camera* camera = &param->camera;
  //---------------------------

  //Compute camera movment speed value
  float cam_speed = camera->speed_move * 0.000016;
  if(fast){
    cam_speed *= 5;
  }

  if(what == "up"){
    camera->cam_P += camera->cam_F * cam_speed;
  }
  else if(what == "down"){
    camera->cam_P -= camera->cam_F * cam_speed;
  }
  else if(what == "right"){
    if(camera->mode == "first_person"){
      camera->cam_P += camera->cam_R * cam_speed;
    }else if(camera->mode == "arcball"){
      vec2 angle =vec2(-cam_speed/10, 0);
      cam_arcball->arcball_viewport_angle(camera, angle);
    }
  }
  else if(what == "left"){
    if(camera->mode == "first_person"){
      camera->cam_P -= camera->cam_R * cam_speed;
    }else if(camera->mode == "arcball"){
      vec2 angle =vec2(cam_speed/10, 0);
      cam_arcball->arcball_viewport_angle(camera, angle);
    }
  }

  //---------------------------
}
void ENG_camera::loop_cam_mouse(){
  Struct_camera* camera = &param->camera;
  //---------------------------

  if(camera->cam_move){
    if(camera->mode == "first_person"){
      cam_fp->fp_cam_mouse(camera);
      ImGui::SetMouseCursor(ImGuiMouseCursor_None);
    }else if(camera->mode == "arcball"){
      cam_arcball->arcball_cam_mouse(camera);
      ImGui::SetMouseCursor(ImGuiMouseCursor_None);
    }
  }

  //---------------------------
}
void ENG_camera::reset(){
  Struct_camera* camera = &param->camera;
  //---------------------------

  camera->reset();

  //---------------------------
}

//MVP Matrix
mat4 ENG_camera::compute_cam_view(){
  Struct_camera* camera = &param->camera;
  mat4 cam_view;
  //---------------------------

  if(camera->cam_pose){
    cam_view = camera->cam_pose_mat;
  }else if(camera->mode == "first_person"){
    cam_view = cam_fp->fp_view_mat(camera);
  }else if(camera->mode == "arcball"){
    camera->cam_COM_obj = arcball_origin;
    cam_view = cam_arcball->arcball_view_mat(camera);
  }

  //---------------------------
  return cam_view;
}
mat4 ENG_camera::compute_cam_proj(){
  Struct_camera* camera = &param->camera;
  mat4 projection;
  //---------------------------

  if(camera->projection == "perspective"){
    projection = cam_proj->compute_proj_perspective(camera);
  }
  else if(camera->projection == "orthographic"){
    projection = cam_proj->compute_proj_ortho(camera);
  }

  //---------------------------
  return projection;
}
mat4 ENG_camera::compute_cam_mvp(){
  //---------------------------

  mat4 cam_modl = mat4(1);
  mat4 cam_view = compute_cam_view();
  mat4 cam_proj = compute_cam_proj();

  mat4 mvpMatrix = cam_proj * cam_view * cam_modl;

  //---------------------------
  return mvpMatrix;
}
void ENG_camera::compute_cam_mvp(Object* object){
  //---------------------------

  mat4 cam_modl = glm::transpose(object->model);
  mat4 cam_view = compute_cam_view();
  mat4 cam_proj = compute_cam_proj();

  object->mvp = cam_proj * cam_view * cam_modl;

  //---------------------------
}

//ENG_camera mode
void ENG_camera::set_mode_projection(int proj){
  Struct_camera* camera = &param->camera;
  //---------------------------

  switch(proj){
    case 0:{ //Perspective
      camera->projection = "perspective";
      break;
    }
    case 1:{ //Orthographic
      camera->projection = "orthographic";
      break;
    }
  }

  //---------------------------
}
void ENG_camera::set_mode_angle(int view){
  Struct_camera* camera = &param->camera;
  //---------------------------

  switch(view){
    case 0:{ //Top
      camera->view = "top";
      break;
    }
    case 1:{ //Oblique
      camera->view = "oblique";
      break;
    }
  }

  //---------------------------
}
void ENG_camera::set_mode_view(int mode){
  Struct_camera* camera = &param->camera;
  //---------------------------

  switch(mode){
    case 0:{ //Default
      camera->mode = "first_person";
      break;
    }
    case 1:{ //Arcball
      camera->mode = "arcball";
      break;
    }
  }

  //---------------------------
}

//Specific function
mat4 ENG_camera::compute_cam_world_pose(){
  Struct_camera* camera = &param->camera;
  //---------------------------

  vec3 zaxis = normalize(camera->cam_F);
  vec3 xaxis = normalize(cross(camera->cam_U, zaxis));
  vec3 yaxis = cross(zaxis, xaxis);

  mat4 absPose(
         xaxis[0], yaxis[0], zaxis[0], camera->cam_P[0],
         xaxis[1], yaxis[1], zaxis[1], camera->cam_P[1],
         xaxis[2], yaxis[2], zaxis[2], camera->cam_P[2],
           0,       0,       0,     1);

  //---------------------------
  return absPose;
}
void ENG_camera::compute_zoom(float value){
  Struct_camera* camera = &param->camera;
  //---------------------------

  cam_zoom->compute_zoom_position(camera, value);

  //---------------------------
}
