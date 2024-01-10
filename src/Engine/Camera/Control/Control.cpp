#include "Control.h"

#include <Engine/Base/Namespace.h>
#include <Engine/Engine.h>
#include <Utility/Namespace.h>
#include <Utility/Element/Namespace.h>


namespace eng::camera{

//Constructor / Destructor
Control::Control(Engine* engine, eng::data::Camera* camera){
  //---------------------------

  util::Node* utility = engine->get_utility();
  util::element::Window* utl_window = utility->get_utl_window();

  this->mode_arcball = new eng::camera::mode::Arcball(utl_window);
  this->mode_player = new eng::camera::mode::Player(utl_window);
  this->camera = camera;

  //---------------------------
}
Control::~Control(){}

//Main function
void Control::control_keyboard(int direction, bool fast){
  //---------------------------

  //Compute camera movment speed value
  float cam_speed = camera->speed_move * 0.000016;
  if(fast){
    cam_speed *= 5;
  }

  switch(direction){
    case CAMERA_UP:{
      camera->cam_P += camera->cam_F * cam_speed;
      break;
    }
    case CAMERA_DOWN:{
      camera->cam_P -= camera->cam_F * cam_speed;
      break;
    }
    case CAMERA_RIGHT:{
      if(camera->mode == "Player"){
        camera->cam_P += camera->cam_R * cam_speed;
      }else if(camera->mode == "arcball"){
        vec2 angle =vec2(-cam_speed/10, 0);
        mode_arcball->rotate_by_angle(camera, angle);
      }
      break;
    }
    case CAMERA_LEFT:{
      if(camera->mode == "Player"){
        camera->cam_P -= camera->cam_R * cam_speed;
      }else if(camera->mode == "arcball"){
        vec2 angle =vec2(cam_speed/10, 0);
        mode_arcball->rotate_by_angle(camera, angle);
      }
      break;
    }
  }

  //---------------------------
}
void Control::control_mouse(){
  //---------------------------

  if(camera->cam_move){
    if(camera->mode == "player")       mode_player->fp_cam_mouse(camera);
    else if(camera->mode == "arcball") mode_arcball->arcball_cam_mouse(camera);
    ImGui::SetMouseCursor(ImGuiMouseCursor_None);
  }

  //---------------------------
}


}
