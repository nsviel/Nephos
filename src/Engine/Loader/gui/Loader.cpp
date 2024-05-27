#include "Loader.h"

#include <Data/Namespace.h>
#include <Loader/Namespace.h>
#include <Operation/Namespace.h>
#include <Utility/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace ldr::gui{

//Constructor / Destructor
Loader::Loader(ldr::Node* node_loader, bool* show_window) : ldr::gui::Navigator(node_loader){
  //---------------------------

  dat::Node* node_data = node_loader->get_node_data();

  this->dat_graph = node_data->get_dat_graph();
  this->dat_set = node_data->get_data_set();
  this->ldr_importer = node_loader->get_ldr_importer();
  this->ldr_bookmark = node_loader->get_ldr_bookmark();
  this->ope_transform = new ope::Transformation();
  this->ope_operation = new ope::Operation();

  this->default_dir = utl::path::get_current_parent_path_abs();
  this->current_dir = default_dir;
  this->name = "Loader";
  this->show_window = show_window;

  //---------------------------
}
Loader::~Loader(){}

//Main function
void Loader::run_panel(){
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
void Loader::design_panel(){
  ImGuiTabItemFlags flag = 0;
  //---------------------------

  if(goto_file_tab){
    flag = ImGuiTabItemFlags_SetSelected;
    this->goto_file_tab = false;
  }

  this->draw_header();
  ImGui::Separator();

  ImVec2 size = ImGui::GetContentRegionAvail();
  if(ImGui::BeginTabBar("Loader_tab##4567")){
    //File manager loader
    ImGui::SetNextItemWidth(size.x/2);
    if(ImGui::BeginTabItem("File##50", NULL, flag)){
      this->draw_navigator();
      ImGui::EndTabItem();
    }

    //Bookmark loader
    ImGui::SetNextItemWidth(size.x/2);
    if(ImGui::BeginTabItem("Bookmark##50", NULL)){
      this->draw_bookmark_tab();
      ImGui::EndTabItem();
    }

    ImGui::EndTabBar();
  }

  //---------------------------
}

//Subfunction
void Loader::draw_header(){
  //---------------------------

  // Load button
  if(ImGui::Button("Load##222")){
    this->operation_selection();
    this->vec_selection.clear();
  }

  // Scale new
  ImGui::SameLine();
  ImGui::SetNextItemWidth(75);
  ImGui::DragFloat("Scale##4567", &param_scaling, 0.1, 0.1, 100, "%.2f x");

  // Remove old
  ImGui::SameLine();
  ImGui::Checkbox("Remove##222", &param_remove_old);

  // Center new
  ImGui::SameLine();
  ImGui::Checkbox("Centered##222", &param_centered);

  //---------------------------
}
void Loader::draw_bookmark_tab(){
  std::list<ldr::bookmark::Item> list_item = ldr_bookmark->get_list_item();
  //---------------------------

  for(int i=0; i<list_item.size(); i++){
    ldr::bookmark::Item& item = *next(list_item.begin(), i);
    ldr::gui::Bookmark bookmark;
    bookmark.item = item;

    //File type icon
    ImVec4 color_icon = ImVec4(bookmark.item.color_icon.r, bookmark.item.color_icon.g, bookmark.item.color_icon.b, bookmark.item.color_icon.a);
    ImGui::TextColored(color_icon, "%s", bookmark.item.icon.c_str());

    //Bookmark name button
    ImGui::SameLine();
    int trash_space = 0;
    bookmark.item.is_supressible ? trash_space = 30 : 0;
    int size = ImGui::GetContentRegionAvail().x - trash_space;
    ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.04, 0.5));
    if(ImGui::Button(bookmark.item.name.c_str(), ImVec2(size, 0))){
      this->operation_bookmark(bookmark.item.path);
    }
    ImGui::PopStyleVar();
    ImGui::SetItemTooltip("%s", bookmark.item.path.c_str());

    //Bookmark supression
    if(bookmark.item.is_supressible){
      ImGui::SameLine();
      std::string ID = bookmark.item.path + "##supressionbookmark";
      ImGui::PushID(ID.c_str());
      if(ImGui::Button(ICON_FA_TRASH "##supressionbookmark")){
        ldr_bookmark->remove_path(bookmark.item.path);
        ldr_bookmark->save_on_file();
      }
      ImGui::PopID();
    }
  }

  //---------------------------
}

//Operation function
void Loader::operation_selection(){
  //---------------------------

  //Retrieve all good selected files to load
  std::vector<std::string> vec_path;
  for(int i=0; i<vec_bookmark_file.size(); i++){
    ldr::gui::Bookmark& bookmark = vec_bookmark_file[i];
    if(vec_selection.contains(bookmark.item.ID)){
      if(ldr_importer->is_format_supported(bookmark.item.format)){
        vec_path.push_back(bookmark.item.path);
      }
    }
  }
  if(vec_path.size() == 0) return;

  //Apply loading and operations
  if(param_remove_old){
    dat::base::Set* set_graph = dat_graph->get_set_graph();
    dat_set->remove_all_entity(set_graph);
  }

  for(int i=0; i<vec_path.size(); i++){
    utl::media::Path path;
    path.data = vec_path[i];

    dat::base::Object* object = ldr_importer->load_object(path);

    if(object != nullptr){
      this->operation_entity(object);
    }
  }

  //---------------------------
}
void Loader::operation_bookmark(std::string file_path){
  //---------------------------

  //If selection is a directory go display his content
  if(utl::directory::is_directory(file_path)){
    this->current_dir = file_path;
    this->goto_file_tab = true;
  }
  //If selection is a file go load it
  else{
    //File check
    std::string format = utl::path::get_format_from_path(file_path);
    if(!utl::file::is_exist(file_path)) return;
    if(!ldr_importer->is_format_supported(format)) return;

    //Apply loading and operations
    if(param_remove_old){
      dat::base::Set* set_graph = dat_graph->get_set_graph();
      dat_set->remove_all_entity(set_graph);
    }

    utl::media::Path path;
    path.data = file_path;
    dat::base::Object* object = ldr_importer->load_object(path);

    if(object != nullptr){
      this->operation_entity(object);
    }
  }

  //---------------------------
}
void Loader::operation_entity(dat::base::Entity* entity){
  //---------------------------


  if(entity != nullptr){
    //Scaling
    //ope_transform->make_scaling(object, param_scaling);

    //Centered
    if(param_centered){
      //ope_operation->center_object(object);
    }
  }

  //---------------------------
}


}
