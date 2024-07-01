#include "Selection.h"

#include <Loader/Namespace.h>
#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace ldr::gui::navigator{

//Constructor / Destructor
Selection::Selection(ldr::gui::navigator::Structure* nav_struct){
  //---------------------------

  this->nav_struct = nav_struct;

  //---------------------------
}
Selection::~Selection(){}

//Main function
void Selection::control_selection(ldr::gui::navigator::File& file, bool& already_selected){
  ImGuiIO& io = ImGui::GetIO();
  //---------------------------

  if(io.KeyCtrl){
    if(already_selected){
      nav_struct->vec_selection.find_erase_unsorted(file.item.ID);
    }
    else{
      nav_struct->vec_selection.push_back(file.item.ID);
    }
  }else{
    nav_struct->vec_selection.clear();
    nav_struct->vec_selection.push_back(file.item.ID);
  }

  //---------------------------
}
void Selection::item_selection_truc(utl::base::Path& path){
  //---------------------------

  int selection = nav_struct->vec_selection[nav_struct->vec_selection.size() - 1];
  for(int i=0; i<nav_struct->vec_file.size(); i++){
    ldr::gui::navigator::File& file = nav_struct->vec_file[i];

    if(file.item.ID == selection){
      path.directory = utl::path::get_dir_from_path(file.item.path);
      path.name = utl::path::get_name_from_path(file.item.path);
      path.format = utl::path::get_format_from_path(file.item.path);
    }
  }

  //---------------------------
}



void Selection::selection_item(ldr::gui::navigator::File& file){
  //---------------------------

  ImGuiSelectableFlags flag;
  flag |= ImGuiSelectableFlags_SpanAllColumns;
  flag |= ImGuiSelectableFlags_AllowOverlap;
  flag |= ImGuiSelectableFlags_AllowDoubleClick;

  bool item_is_selected = nav_struct->vec_selection.contains(file.item.ID);
  std::string label = "##" + std::to_string(file.item.ID);
  ImGui::SameLine();
  if(ImGui::Selectable(label.c_str(), item_is_selected, flag)){
    this->control_selection(file, item_is_selected);

    if(file.item.type == ldr::bookmark::FOLDER){
      this->selection_folder(file);
    }else{
      this->selection_file(file);
    }

  }

  //---------------------------
}
void Selection::selection_file(ldr::gui::navigator::File& file){
  //---------------------------

  //If double clicked, load it
  if(ImGui::IsMouseDoubleClicked(0)){
    nav_struct->vec_selection.clear();
    nav_struct->vec_selection.push_back(file.item.ID);
    //this->item_operation();
  }

  //---------------------------
}
void Selection::selection_folder(ldr::gui::navigator::File& file){
  //---------------------------
/*
  //If double clicked, enter in it
  if(ImGui::IsMouseDoubleClicked(0)){
    if(file.item.name == ".."){
      std::filesystem::path fs_path = path.directory;
      path.directory = fs_path.parent_path();
      nav_struct->vec_selection.clear();
    }else{
      path.directory += "/" + file.item.name;
      nav_struct->vec_selection.clear();
    }
  }
*/
  //---------------------------
}




}
