#include "Node.h"

#include <imgui/editor/node/imgui_node_editor.h>


namespace utl::gui::editor{

//Constructor / Destructor
Node::Node(){
  //---------------------------


  //---------------------------
}
Node::~Node(){}

//Main function
void Node::design_panel(){
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
void Node::node_editor(){
  //---------------------------

  //Example exampe;

  //if(exampe.Create())
    //  return exampe.Run();

  //---------------------------
}

}
