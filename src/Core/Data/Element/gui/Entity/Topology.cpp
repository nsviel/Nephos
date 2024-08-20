#include "Topology.h"

#include <Data/Element/Namespace.h>
#include <Utility/Namespace.h>
#include <imgui/core/imgui.h>


namespace dat::gui::entity{

//Constructor / Destructor
Topology::Topology(){
  //---------------------------

  //---------------------------
}
Topology::~Topology(){}

//Main function
void Topology::entity_typology(dat::base::Entity* entity){
  utl::base::Data* data = &entity->data;
  if(data == nullptr) return;
  //---------------------------

  //Primitive size
  switch(data->topology.type){
    case utl::topology::POINT:{
      this->topology_point(data);
      break;
    }
    case utl::topology::LINE:{
      this->topology_line(data);
      break;
    }
    case utl::topology::TRIANGLE:{
      this->topology_triangle(data);
      break;
    }
  }

  //---------------------------
}

//Subfunction
void Topology::topology_line(utl::base::Data* data){
  ImGuiStyle& style = ImGui::GetStyle();
  //---------------------------

  ImVec4 color = ImVec4(0.2330f, 0.5392f, 0.6686f, 1.0f);

  //Draw type
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Topology"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "line");

  //Number of points
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Count"); ImGui::TableNextColumn();
  std::string nb_point = math::thousand_separator(data->size / 2);
  ImGui::TextColored(color, "%s", nb_point.c_str());

  //Line width
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Line width"); ImGui::TableNextColumn();
  ImGui::PushButtonRepeat(true);
  if(ImGui::ArrowButton("##left", ImGuiDir_Left)){
    data->topology.width--;

    if(data->topology.width <= 1){
      data->topology.width = 1;
    }
  }
  ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
  if(ImGui::ArrowButton("##right", ImGuiDir_Right)){
    data->topology.width++;
  }
  ImGui::PopButtonRepeat();
  ImGui::SameLine();
  ImGui::TextColored(color, "%d", data->topology.width);

  //---------------------------
}
void Topology::topology_point(utl::base::Data* data){
  ImGuiStyle& style = ImGui::GetStyle();
  //---------------------------

  ImVec4 color = ImVec4(0.2330f, 0.5392f, 0.6686f, 1.0f);

  //Draw type
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Topology"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "point");

  //Number of points
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Count"); ImGui::TableNextColumn();
  std::string nb_point = math::thousand_separator(data->size);
  ImGui::TextColored(color, "%s", nb_point.c_str());

  //Point size
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Size"); ImGui::TableNextColumn();
  ImGui::PushButtonRepeat(true);
  if(ImGui::ArrowButton("##left", ImGuiDir_Left)){
    data->topology.width--;

    if(data->topology.width <= 1){
      data->topology.width = 1;
    }
  }
  ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
  if(ImGui::ArrowButton("##right", ImGuiDir_Right)){
    data->topology.width++;
  }
  ImGui::PopButtonRepeat();
  ImGui::SameLine();
  ImGui::TextColored(color, "%d", data->topology.width);

  //---------------------------
}
void Topology::topology_triangle(utl::base::Data* data){
  ImGuiStyle& style = ImGui::GetStyle();
  //---------------------------

  ImVec4 color = ImVec4(0.2330f, 0.5392f, 0.6686f, 1.0f);

  //Draw type
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Topology"); ImGui::TableNextColumn();
  ImGui::TextColored(color, "triangle");

  //Number of points
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Count"); ImGui::TableNextColumn();
  std::string nb_point = math::thousand_separator(data->size / 3);
  ImGui::TextColored(color, "%s", nb_point.c_str());

  //---------------------------
}

}
