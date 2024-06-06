#include "Panel.h"

#include <Data/Namespace.h>
#include <Loader/Namespace.h>
#include <Operation/Namespace.h>
#include <Utility/Namespace.h>
#include <Dynamic/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace ldr::gui::exporter{

//Constructor / Destructor
Panel::Panel(ldr::Node* node_loader, bool* show_window) : ldr::gui::Navigator(node_loader){
  //---------------------------

  dat::Node* node_data = node_loader->get_node_data();

  this->ldr_struct = node_loader->get_ldr_struct();
  this->dat_selection = node_data->get_dat_selection();
  this->ldr_exporter = node_loader->get_ldr_exporter();

  this->name = "Export##555";
  this->show_window = show_window;
  this->with_bookmark = false;
  this->with_all_format = false;
  this->current_format = "ply";

  //---------------------------
}
Panel::~Panel(){}

//Main function
void Panel::run_panel(){
  //---------------------------

  if(*show_window){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    ImGui::SetNextWindowSizeConstraints(ImVec2(300, 300), ImVec2(400, FLT_MAX));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){

      this->design_panel();

      ImGui::End();
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Panel::design_panel(){
  dat::base::Entity* entity = dat_selection->get_selected_entity();
  //---------------------------

  //If dynamic, record
  bool exporter = true;
  if(dyn::base::Sensor* sensor = dynamic_cast<dyn::base::Sensor*>(entity)){
    exporter = false;
  }


  this->item_update();

  this->display_action();
  this->display_path();
  this->display_format();
  this->display_encording();
  this->draw_navigator();

  //---------------------------
  ImGui::Separator();
}

//Header function
void Panel::display_action(){
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(80, 100, 80, 255));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(60, 80, 60, 255));
  if(ImGui::Button("Save##444", ImVec2(ImGui::GetContentRegionAvail().x, 0))){
    this->item_operation();
    this->vec_selection.clear();
  }
  ImGui::PopStyleColor(2);

  //---------------------------
}
void Panel::display_path(){
  //---------------------------

  ImGui::BeginTable("header##exporter", 2);
  ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 50.0f);
  ImGui::TableSetupColumn("two", ImGuiTableColumnFlags_WidthStretch);

  //Directory
  static char str_n[256];
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Directory"); ImGui::TableNextColumn();
  strncpy(str_n, current_dir.c_str(), sizeof(str_n) - 1);
  ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
  ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.4f, 1.0f, 0.4f, 1.0f));
  ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
  if(ImGui::InputText("##exporter_dir", str_n, IM_ARRAYSIZE(str_n))){
    this->current_dir = (string)str_n;
  }
  ImGui::PopStyleColor(2);

  //Filename
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Name"); ImGui::TableNextColumn();
  strncpy(str_n, current_name.c_str(), sizeof(str_n) - 1);
  ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
  ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.4f, 1.0f, 0.4f, 1.0f));
  ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
  if(ImGui::InputText("##exporter_name", str_n, IM_ARRAYSIZE(str_n))){
    this->current_name = (string)str_n;
  }
  ImGui::PopStyleColor(2);

  ImGui::EndTable();

  //---------------------------
  ImGui::Separator();
}
void Panel::display_format(){
  //---------------------------

  ImGui::BeginTable("header##exporter", 2);
  ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 50.0f);
  ImGui::TableSetupColumn("two", ImGuiTableColumnFlags_WidthStretch);

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Format"); ImGui::TableNextColumn();
  static int format = 0;
  std::vector<std::string> vec_format = ldr_exporter->get_supported_format();
  for(int i=0; i<vec_format.size(); i++){
    if(ImGui::RadioButton(vec_format[i].c_str(), &format, i)){
      this->current_format = vec_format[i];
    }
  }

  ImGui::EndTable();

  //---------------------------
}
void Panel::display_encording(){
  //---------------------------

  ImGui::BeginTable("header##exporter", 2);
  ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 50.0f);
  ImGui::TableSetupColumn("two", ImGuiTableColumnFlags_WidthStretch);

  std::vector<int> vec_encoding = ldr_exporter->get_supported_encoding(current_format);
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  ImGui::Text("Encoding"); ImGui::TableNextColumn();
  static int mode = 1;
  bool condition = (std::find(vec_encoding.begin(), vec_encoding.end(), ldr::io::ASCII) == vec_encoding.end());
  if(condition){
    ImGui::BeginDisabled();
    mode = ldr::io::BINARY;
  }
  if(ImGui::RadioButton("ASCII", &mode, ldr::io::ASCII)){
    ldr_struct->export_encoding = ldr::io::ASCII;
  }
  if(condition) ImGui::EndDisabled();
  ImGui::SameLine();
  condition = (std::find(vec_encoding.begin(), vec_encoding.end(), ldr::io::BINARY) == vec_encoding.end());
  if(condition){
    ImGui::BeginDisabled();
    mode = ldr::io::ASCII;
  }
  if(ImGui::RadioButton("Binary", &mode, ldr::io::BINARY)){
    ldr_struct->export_encoding = ldr::io::BINARY;
  }
  if(condition) ImGui::EndDisabled();

  ImGui::EndTable();

  //---------------------------
  ImGui::Separator();
}

//Navigator function
void Panel::item_update(){
  dat::base::Entity* entity = dat_selection->get_selected_entity();
  //---------------------------

  //Actualize current name
  if(entity != nullptr && current_name != entity->name){
    utl::base::Data* data = &entity->data;
    this->current_name = entity->name;

    if(ldr_exporter->is_format_supported(data->format)){
      this->current_format = data->format;
    }
  }

  //---------------------------
}
void Panel::item_operation(){
  dat::base::Entity* entity = dat_selection->get_selected_entity();
  if(entity == nullptr) return;
  //---------------------------

  utl::base::Data* data = &entity->data;
  data->format = current_format;

  std::string path = current_dir + "/" + current_name + "." + current_format;
  ldr_exporter->export_entity(entity, path);

  //---------------------------
}
bool Panel::item_format(std::string format){
  //---------------------------

  return ldr_exporter->is_format_supported(format);

  //---------------------------
}

}
