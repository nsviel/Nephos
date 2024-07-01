#include "Docking.h"

#include <GUI/Namespace.h>
#include <imgui/core/imgui.h>
#include <iostream>


namespace gui::interface{

//Constructor / Destructor
Docking::Docking(gui::Node* gui){
  //---------------------------


  //---------------------------
}
Docking::~Docking(){}

//Main function
void Docking::loop(){
  //---------------------------

  this->docking_space();

  //---------------------------
}

//Subfunction
void Docking::docking_space(){
  ImGuiIO& io = ImGui::GetIO();
  //---------------------------

  // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
  // because it would be confusing to have two docking targets within each others.

  ImGuiViewport* viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(viewport->Pos);
  ImGui::SetNextWindowSize(viewport->Size);
  ImGui::SetNextWindowViewport(viewport->ID);

  ImGuiWindowFlags flag;
  flag |= ImGuiWindowFlags_MenuBar;
  flag |= ImGuiWindowFlags_NoDocking;
  flag |= ImGuiWindowFlags_NoTitleBar;
  flag |= ImGuiWindowFlags_NoCollapse;
  flag |= ImGuiWindowFlags_NoResize;
  flag |= ImGuiWindowFlags_NoMove;
  flag |= ImGuiWindowFlags_NoBringToFrontOnFocus;
  flag |= ImGuiWindowFlags_NoNavFocus;
  flag |= ImGuiWindowFlags_NoBackground;

  // Main dock space
  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::Begin("dock_space_main", nullptr, flag);
  ImGui::PopStyleVar(3);

  if(io.ConfigFlags & ImGuiConfigFlags_DockingEnable){
  	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
  	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
  }

  ImGui::End();

  //---------------------------
}

}
