#include "Panel.h"

#include <Engine/Transformation/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>


namespace eng::trf::gui{

//Constructor / Destructor
Panel::Panel(eng::trf::Node* node_transfo, bool* show_window){
  //---------------------------

  dat::Node* node_data = node_transfo->get_node_data();
  dat::gph::Node* node_graph = node_data->get_node_graph();

  this->trf_io = node_transfo->get_trf_io();
  this->gph_selection = node_graph->get_gph_selection();
  this->gui_navigator = new utl::gui::Navigator();

  this->name = "Transformation##555";
  this->show_window = show_window;

  //---------------------------
}
Panel::~Panel(){}

//Main function
void Panel::run_panel(){
  std::shared_ptr<utl::base::Element> element = gph_selection->get_selected_element();
  if(!element) return;
  //---------------------------

  if(*show_window){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    ImGui::SetNextWindowSizeConstraints(ImVec2(300, 300), ImVec2(400, FLT_MAX));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){

      this->design_panel(element);

      ImGui::End();
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Panel::design_panel(std::shared_ptr<utl::base::Element> element){
  //---------------------------

  trf_io->update_path(element);

  this->display_loader(element);
  this->display_path(element);
  this->display_format(element);
  this->display_matrix(element);
  gui_navigator->draw_navigator(*trf_io->get_path());

  //---------------------------
}

//Subfunction
void Panel::display_loader(std::shared_ptr<utl::base::Element> element){
  //---------------------------

  float width = ImGui::GetContentRegionAvail().x;

  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
  if(ImGui::Button("Load##transformation", ImVec2(width / 2, 0))){
    this->item_operation();
  }
  ImGui::PopStyleColor(2);
  ImGui::SameLine();
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
  if(ImGui::Button("Save##transformation", ImVec2(width / 2, 0))){
    this->item_operation();
  }
  ImGui::PopStyleColor(2);

  //---------------------------
}
void Panel::display_path(std::shared_ptr<utl::base::Element> element){
  utl::base::Path* path = trf_io->get_path();
  //---------------------------

  ImGui::BeginTable("header##exporter", 3);
  ImGui::TableSetupColumn("1", ImGuiTableColumnFlags_WidthFixed, 50.0f);
  ImGui::TableSetupColumn("2", ImGuiTableColumnFlags_WidthStretch);
  ImGui::TableSetupColumn("3", ImGuiTableColumnFlags_WidthFixed, 25.0f);

  //Directory
  static char str_n[256];
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Directory"); ImGui::TableNextColumn();
  ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
  ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.4f, 1.0f, 0.4f, 1.0f));
  std::string current_path = path->directory;
  if(current_path == "") current_path = "(not defined)";
  ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "%s", current_path.c_str());
  ImGui::PopStyleColor();
  ImGui::TableNextColumn();
  if(ImGui::Button(ICON_FA_FOLDER "##folder_path")){
    utl::directory::open(path->directory);
  }

  //Filename
  if(auto entity = std::dynamic_pointer_cast<dat::base::Entity>(element)){
    ImGui::TableNextRow(); ImGui::TableNextColumn();
    ImGui::Text("Name"); ImGui::TableNextColumn();
    strncpy(str_n, path->name.c_str(), sizeof(str_n) - 1);
    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.4f, 1.0f, 0.4f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
    if(ImGui::InputText("##exporter_name", str_n, IM_ARRAYSIZE(str_n))){
      path->name = (std::string)str_n;
    }
    ImGui::PopStyleColor(2);
  }

  ImGui::EndTable();

  //---------------------------
}
void Panel::display_format(std::shared_ptr<utl::base::Element> element){
  utl::base::Path* path = trf_io->get_path();
  //---------------------------

  ImGui::BeginTable("format##transformation", 2);
  ImGui::TableSetupColumn("1", ImGuiTableColumnFlags_WidthFixed, 50.0f);
  ImGui::TableSetupColumn("1", ImGuiTableColumnFlags_WidthStretch);

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Format"); ImGui::TableNextColumn();
  static int format = 0;
  std::vector<std::string> vec_format = trf_io->get_supported_format();
  for(int i=0; i<vec_format.size(); i++){
    if(ImGui::RadioButton(vec_format[i].c_str(), &format, i)){
      path->format = vec_format[i];
    }
  }

  ImGui::EndTable();

  //---------------------------
  ImGui::Separator();
}
void Panel::display_matrix(std::shared_ptr<utl::base::Element> element){
  utl::base::Pose& pose = element->pose;
  //---------------------------

  //Model matrix
  ImVec2 width = ImGui::GetContentRegionAvail();
  glm::mat4& model = pose.model;
  ImGui::Columns(4, "ModelMat");
  for(int i=0; i<4; i++){
    ImGui::Separator();
    for(int j=0; j<4; j++){
      ImGui::Text("%.3f", model[i][j]);
      ImGui::NextColumn();
    }
  }
  ImGui::Separator();
  ImGui::Columns(1);

  //---------------------------
  ImGui::Separator();
}
void Panel::item_filtering(std::vector<std::string>& vec_path){
  //---------------------------

  std::vector<std::string> vec_path_ok;
  for(int i=0; i<vec_path.size(); i++){
    std::string& path = vec_path[i];

    //If direcctory, ok
    if(utl::directory::is_directory(path)){
      vec_path_ok.push_back(path);
      continue;
    }

    //If file, check format compatibility
    std::string format = utl::path::get_format_from_path(path);
    if(format == "json"){
      vec_path_ok.push_back(vec_path[i]);
    }
  }

  //---------------------------
  vec_path = vec_path_ok;
}
void Panel::item_operation(){
  std::shared_ptr<utl::base::Element> element = gph_selection->get_selected_element();
  if(!element) return;
  //---------------------------

  utl::base::Path* path = trf_io->get_path();
  std::string path_file = path->build();
  trf_io->load_transformation(element, path_file);

  //---------------------------
}

}
