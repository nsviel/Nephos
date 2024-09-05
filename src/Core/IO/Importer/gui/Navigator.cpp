#include "Navigator.h"

#include <IO/Importer/Namespace.h>
#include <Utility/Namespace.h>


namespace io::imp::gui{

//Constructor / Destructor
Navigator::Navigator(io::imp::gui::Panel* gui_panel){
  //---------------------------

  io::imp::Node* node_importer = gui_panel->get_node_importer();

  this->io_struct = node_importer->get_io_struct();
  this->io_loader = node_importer->get_io_loader();
  this->utl_navigator = gui_panel->get_utl_navigator();

  //---------------------------
  this->init_navigator();
}
Navigator::~Navigator(){}

//Main function
void Navigator::init_navigator(){
  //---------------------------

  utl_navigator->add_fct_item_operation([this](utl::base::Path path){this->item_operation(path);});

  //---------------------------
}
void Navigator::draw_tab(int width){
  //---------------------------

  //Flag to force navigator tab in case of bookmark folder
  ImGuiTabItemFlags flag = 0;
  if(io_struct->open_navigation){
    flag = ImGuiTabItemFlags_SetSelected;
    io_struct->open_navigation = false;
  }

  ImGui::SetNextItemWidth(width);
  if(ImGui::BeginTabItem("Navigator##50", NULL, flag)){
    utl_navigator->draw_navigator(io_struct->path);
    ImGui::EndTabItem();
  }

  //---------------------------
}
void Navigator::item_operation(utl::base::Path utl_path){
  //---------------------------

  std::string path = utl_path.build();
  if(utl::path::is_dir_or_file(path) == "file"){
    io_loader->load_object(utl_path);
  }else{
    io_loader->load_directory(utl_path);
  }

  //---------------------------
}

}
