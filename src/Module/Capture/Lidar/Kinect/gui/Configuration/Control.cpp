#include "Control.h"

#include <Kinect/Namespace.h>


namespace k4n::gui{

//Constructor / Destructor
Control::Control(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_swarm = node_k4n->get_k4n_swarm();

  //---------------------------
}
Control::~Control(){}

//Main function
void Control::run_control(){
  //---------------------------

  this->control_keyboard();

  //---------------------------
}

//Keyboard
void Control::control_keyboard(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  for(int i=0; i<IM_ARRAYSIZE(io.KeysDown); i++){
    k4n::dev::Master* master = k4n_swarm->get_selected_master();

    //Tab key
    if(ImGui::IsKeyPressed(ImGuiKey_Space)){
      master->player_pause(!master->player->pause);
      break;
    }

    //Left arrow key
    if(ImGui::IsKeyPressed(ImGuiKey_LeftArrow)){
      master->player->ts_forward = -1;
      break;
    }

    //Right arrow key
    if(ImGui::IsKeyPressed(ImGuiKey_RightArrow)){
      master->player->ts_forward = 1;
      break;
    }
  }

  //---------------------------
}


}
