#include "Panel.h"

#include <Data/Attribut/Namespace.h>
#include <Data/Graph/Namespace.h>
#include <Utility/Namespace.h>
#include <imgui/core/imgui.h>


namespace dat::atr::gui{

//Constructor / Destructor
Panel::Panel(dat::atr::Node* node_attribut){
  //---------------------------

  dat::gph::Node* node_graph = node_attribut->get_node_graph();

  this->gui_color = new dat::atr::gui::Color(node_attribut);
  this->gui_normal = new dat::atr::gui::Normal(node_attribut);
  this->gph_selection = node_graph->get_gph_selection();

  this->panel_show = true;
  this->panel_name = "Attribut";
  this->item_width = 100;

  //---------------------------
}
Panel::~Panel(){}

//Main function
void Panel::run_panel(){
  //---------------------------

  if(panel_show){
    ImGuiWindowFlags flag;
    flag |= ImGuiWindowFlags_NoCollapse;
    flag |= ImGuiWindowFlags_AlwaysAutoResize;

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.2, 0.2, 0.2, 1));
    if(ImGui::Begin(panel_name.c_str(), &panel_show, flag) == 1){

      this->design_panel();

      ImGui::End();
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Panel::design_panel(){
  std::shared_ptr<utl::base::Element> element = gph_selection->get_selected_element();
  //---------------------------

  gui_color->design_colorization(element);
  gui_normal->design_normal();
  
  //---------------------------
}
void Panel::close_panel(){
  //---------------------------

  this->panel_show = false;

  //---------------------------
}

//Subfunction


}
