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
  this->mode_player = new eng::camera::mode::First_person(utl_window);
  this->camera = camera;

  //---------------------------
}
Control::~Control(){}

//Main function
void Control::control_keyboard(string direction, bool fast){
  //---------------------------

  //Compute camera movment speed value
  float cam_speed = camera->speed_move * 0.000016;
  if(fast){
    cam_speed *= 5;
  }

  if(direction == "up"){
    camera->cam_P += camera->cam_F * cam_speed;
  }
  else if(direction == "down"){
    camera->cam_P -= camera->cam_F * cam_speed;
  }
  else if(direction == "right"){
    if(camera->mode == "first_person"){
      camera->cam_P += camera->cam_R * cam_speed;
    }else if(camera->mode == "arcball"){
      vec2 angle =vec2(-cam_speed/10, 0);
      mode_arcball->arcball_viewport_angle(camera, angle);
    }
  }
  else if(direction == "left"){
    if(camera->mode == "first_person"){
      camera->cam_P -= camera->cam_R * cam_speed;
    }else if(camera->mode == "arcball"){
      vec2 angle =vec2(cam_speed/10, 0);
      mode_arcball->arcball_viewport_angle(camera, angle);
    }
  }

  //---------------------------
}
void Control::control_mouse(){
  //---------------------------

  if(camera->cam_move){
    if(camera->mode == "first_person"){
      mode_player->fp_cam_mouse(camera);
      ImGui::SetMouseCursor(ImGuiMouseCursor_None);
    }else if(camera->mode == "arcball"){
      mode_arcball->arcball_cam_mouse(camera);
      ImGui::SetMouseCursor(ImGuiMouseCursor_None);
    }
  }

  //---------------------------
}

//Camera mode
void Control::set_mode_projection(int proj){
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
void Control::set_mode_view(int mode){
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


}
