#include "Panel.h"

#include <LLMR/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>


namespace llmr::gui{

//Constructor / Destructor
Panel::Panel(llmr::Node* node_llmr, bool* show_window){
  //---------------------------

  dat::Node* node_data = node_llmr->get_node_data();
  dat::gph::Node* node_graph = node_data->get_node_graph();

  this->gph_selection = node_graph->get_gph_selection();
  this->llmr_interface = node_llmr->get_llmr_interface();

  this->show_window = show_window;
  this->name = "LLMR";

  //---------------------------
}
Panel::~Panel(){}

//Main function
void Panel::run_panel(){
  std::shared_ptr<dat::base::Entity> entity = gph_selection->get_selected_entity();
  //---------------------------

  if(*show_window){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSizeConstraints(ImVec2(300, 300), ImVec2(600, 600));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){

      this->design_panel(*entity);

      ImGui::End();
    }
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Panel::design_panel(dat::base::Entity& entity){
  //---------------------------

  this->prompt_input(entity);

  //---------------------------
}

//Subfunction
void Panel::prompt_input(dat::base::Entity& entity){
  //---------------------------

  //Text input
  ImVec2 size(-1, 20);
  static char buffer[1024*16] = "";
  ImGui::InputTextMultiline("##prompt", buffer, sizeof(buffer), ImVec2(-1, 100));

  //Submit button
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
  if(ImGui::Button("Submit##222", ImVec2(-1, 0))){
    std::string str(buffer);
    llmr_interface->send_llm_message(str);
    memset(buffer, 0, sizeof(buffer));
  }
  ImGui::PopStyleColor(2);

  //---------------------------
}

}
