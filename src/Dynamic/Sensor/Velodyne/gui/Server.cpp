#include "Server.h"

#include <Velodyne/Namespace.h>
#include <imgui/core/imgui.h>


namespace vld::gui{

//Constructor / Destructor
Server::Server(vld::Node* node_velodyne){
  //---------------------------

  this->vld_struct = node_velodyne->get_vld_struct();

  //---------------------------
}
Server::~Server(){}

//Main function
void Server::design_server(){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Socket");

  ImGui::BeginTable("##socket_gui", 2);
  //Port
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Port"); ImGui::TableNextColumn();
  ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "%d", vld_struct->server.port);

  //Listening
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Listening"); ImGui::TableNextColumn();
  bool listen = vld_struct->server.is_listening;
  if(listen){
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.4f, 1.0f, 0.4f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.4f, 1.0f, 0.4f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.4f, 1.0f, 0.4f, 1.0f));
    ImGui::Button("##socket_is_listening", ImVec2(15, 15));
    ImGui::PopStyleColor(3);
  }else{
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.4f, 0.4f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.4f, 0.4f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.4f, 0.4f, 1.0f));
    ImGui::Button("##socket_is_listening", ImVec2(15, 15));
    ImGui::PopStyleColor(3);
  }

  ImGui::EndTable();

  //---------------------------
  ImGui::Separator();
}

}
