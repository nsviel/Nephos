//https://github.com/thedmd/imgui-node-editor
#include "EDI_node.h"
#include <GUI.h>


//Constructor / Destructor
EDI_node::EDI_node(EDI_node* gui){
  //---------------------------


  //---------------------------
}
EDI_node::~EDI_node(){}

//Main function
void EDI_node::design_panel(){
  //---------------------------

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::SetNextWindowSizeConstraints(ImVec2(100, 100), ImVec2(500, 500));
  ImGui::Begin("Node editor");
  this->node_editor();
  ImGui::End();
  ImGui::PopStyleVar();

  //---------------------------
}

//Subfunction
void EDI_node::node_editor(){
  //---------------------------

  //Example exampe;

  //if (exampe.Create())
    //  return exampe.Run();

  //---------------------------
}
