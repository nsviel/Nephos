#include "Control.h"

#include <Engine/Base/Namespace.h>
#include <Engine/Engine.h>
#include <Utility/Namespace.h>
#include <Utility/Element/Namespace.h>


namespace eng::camera{

//Constructor / Destructor
Control::Control(Engine* engine){
  //---------------------------

  util::Node* utility = engine->get_utility();
  util::element::Window* utl_window = utility->get_utl_window();

  this->cam_arcball = new eng::camera::mode::Arcball(utl_window);

  //---------------------------
}
Control::~Control(){}

//Main function
void Control::control(string what, bool fast){
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

}
