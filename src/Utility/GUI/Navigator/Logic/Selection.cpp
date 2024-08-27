#include "Selection.h"

#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace utl::gui::navigator{

//Constructor / Destructor
Selection::Selection(utl::gui::Navigator* navigator){
  //---------------------------

  this->nav_struct = navigator->get_nav_struct();

  //---------------------------
}
Selection::~Selection(){}

//Main function
void Selection::selection_item(utl::base::Path& path, utl::gui::navigator::Item& item){
  //---------------------------

  ImGuiSelectableFlags flag;
  flag |= ImGuiSelectableFlags_SpanAllColumns;
  flag |= ImGuiSelectableFlags_AllowOverlap;
  flag |= ImGuiSelectableFlags_AllowDoubleClick;

  bool item_is_selected = nav_struct->vec_selected_idx.contains(item.ID);
  std::string label = "##" + std::to_string(item.ID);
  ImGui::SameLine();
  if(ImGui::Selectable(label.c_str(), item_is_selected, flag)){
    this->control_selection(path, item, item_is_selected);

    //Double click
    if(ImGui::IsMouseDoubleClicked(0)){
      this->double_click(path, item);
    }
  }

  //---------------------------
}

//Subfunction
void Selection::control_selection(utl::base::Path& path, utl::gui::navigator::Item& item, bool& already_selected){
  ImGuiIO& io = ImGui::GetIO();
  //---------------------------

  if(io.KeyCtrl){
    if(already_selected){
      nav_struct->vec_selected_idx.find_erase_unsorted(item.ID);
      this->update_selected_path();
    }
    else if(item.name != ".."){
      nav_struct->vec_selected_idx.push_back(item.ID);
      this->update_selected_path();
    }
  }else if(item.name != ".."){
    this->clear_selection();
    nav_struct->vec_selected_idx.push_back(item.ID);
    this->update_selected_path();
  }

  //---------------------------
}
void Selection::double_click(utl::base::Path& path, utl::gui::navigator::Item& item){
  //---------------------------

  if(item.type == utl::gui::navigator::FOLDER){
    if(item.name == ".."){
      if(path.directory != "/home/") path.directory = utl::path::get_parent_path(path.directory);
      this->clear_selection();
    }else{
      std::string item_name = item.name;
      if(item.type == utl::gui::navigator::FOLDER) item_name += "/";
      path.directory += item_name;
      this->clear_selection();
    }
  }else{
    this->clear_selection();
    nav_struct->vec_selected_idx.push_back(item.ID);
    this->item_operation();
  }

  //---------------------------
}
void Selection::clear_selection(){
  //---------------------------

  nav_struct->vec_selected_idx.clear();
  this->update_selected_path();

  //---------------------------
}
void Selection::item_operation(){
  //---------------------------

  if(!nav_struct->fct_item_operation){
    std::cerr << "[error] No function set in Navigator" << std::endl;
    return;
  }

  //Retrieve all selected files to load
  std::vector<std::string> vec_path;
  for(int i=0; i<nav_struct->vec_item.size(); i++){
    utl::gui::navigator::Item& item = nav_struct->vec_item[i];

    if(nav_struct->vec_selected_idx.contains(item.ID)){
      vec_path.push_back(item.path);
    }
  }

  //Run all file loading
  for(int i=0; i<vec_path.size(); i++){
    utl::base::Path path(vec_path[i]);
    nav_struct->fct_item_operation(path);
  }

  this->clear_selection();

  //---------------------------
}
void Selection::update_selected_path(){
  //---------------------------

  nav_struct->vec_selected_path.clear();
  for(int i=0; i<nav_struct->vec_item.size(); i++){
    utl::gui::navigator::Item& item = nav_struct->vec_item[i];

    if(nav_struct->vec_selected_idx.contains(item.ID)){
      nav_struct->vec_selected_path.push_back(item.path);
    }
  }

  //---------------------------
}

}
