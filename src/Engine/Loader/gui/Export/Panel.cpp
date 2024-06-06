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
  this->gui_exporter = new ldr::gui::exporter::Exporter(node_loader);
  this->gui_recorder = new ldr::gui::exporter::Recorder(node_loader);

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

  this->item_update();

  //If dynamic object
  if(dyn::base::Sensor* sensor = dynamic_cast<dyn::base::Sensor*>(entity)){
    gui_recorder->design_header();
  }
  //Else, it's static object
  else{
    gui_exporter->design_header();
  }

  this->draw_navigator();

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
