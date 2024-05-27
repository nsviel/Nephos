#include "Control.h"

#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>


namespace dyn::gui{

//Constructor / Destructor
Control::Control(dyn::Node* node_dynamic){
  //---------------------------

  dat::Node* node_data = node_dynamic->get_node_data();

  this->dat_graph = node_data->get_dat_graph();

  //---------------------------
}
Control::~Control(){}

//Main function
void Control::run_control(){
  dat::base::Set* set = dat_graph->get_selected_set();
  dyn::base::Player* player = set->player;
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
