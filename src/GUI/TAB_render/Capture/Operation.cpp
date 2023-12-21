#include "Operation.h"

#include <Node/GUI.h>
#include <Engine/Capture/K4A/Device/K4A_swarm.h>


namespace gui::kinect{

//Constructor / Destructor
Operation::Operation(eng::kinect::Kinect* kinect){
  //---------------------------

  this->kinect = kinect;
  this->k4a_swarm = kinect->get_k4a_swarm();

  this->item_width = 100;

  //---------------------------
}
Operation::~Operation(){}

//Main function
void Operation::kinect_operation(){
  //---------------------------

  if(ImGui::TreeNode("Operation")){
    this->colorization();

    ImGui::Separator();
    ImGui::TreePop();
  }

  //---------------------------
}

//Subfunction
void Operation::colorization(){
  //---------------------------
/*
  static int item_current_2 = 0;
  const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK", "LLLLLLL", "MMMM", "OOOOOOO" };

  ImGui::Combo("combo 2 (one-liner)", &item_current_2, "aaaa\0bbbb\0cccc\0dddd\0eeee\0\0");

*/
  //---------------------------
}

}
