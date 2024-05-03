#include "Control.h"

#include <Dynamic/Namespace.h>


namespace dyn::gui{

//Constructor / Destructor
Control::Control(){
  //---------------------------


  //---------------------------
}
Control::~Control(){}

//Main function
void Control::run_control(dyn::base::Player* player){
  //---------------------------

  this->control_keyboard(player);

  //---------------------------
}

//Keyboard
void Control::control_keyboard(dyn::base::Player* player){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  for(int i=0; i<IM_ARRAYSIZE(io.KeysDown); i++){

    //Tab key
    if(ImGui::IsKeyPressed(ImGuiKey_Space)){
      player->player_pause();
      break;
    }

    //Left arrow key
    if(ImGui::IsKeyPressed(ImGuiKey_LeftArrow)){
      //player->ts_forward = -1;
      break;
    }

    //Right arrow key
    if(ImGui::IsKeyPressed(ImGuiKey_RightArrow)){
      //player->ts_forward = 1;
      break;
    }
  }

  //---------------------------
}


}
