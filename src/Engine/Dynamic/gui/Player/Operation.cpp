#include "Operation.h"

#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace dyn::gui{

//Constructor / Destructor
Operation::Operation(dyn::Node* node_dynamic){
  //---------------------------

  this->ope_operation = new ope::Operation();

  //---------------------------
}
Operation::~Operation(){}

//Main function
void Operation::player_transfo(dat::base::Set* set){
  //---------------------------

  //Centered
  if(ImGui::Button("C##centerentity", ImVec2(20, 0))){
    ope_operation->center_object(set);
  }

  //Rotation 90° around X axis
  ImGui::SameLine();
  if(ImGui::Button(ICON_FA_ARROWS_ROTATE "##xrotation")){
    ope_operation->make_rotation_X_90d(set, 1);
  }

  //---------------------------
}

}
