#include "Selection.h"

#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace utl::gui::navigator{

//Constructor / Destructor
Selection::Selection(utl::gui::navigator::Structure* nav_struct){
  //---------------------------

  this->nav_struct = nav_struct;

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

  bool item_is_selected = vec_selection.contains(item.ID);
  std::string label = "##" + std::to_string(item.ID);
  ImGui::SameLine();
  if(ImGui::Selectable(label.c_str(), item_is_selected, flag)){
    this->control_selection(item, item_is_selected);

    //Double click
    if(ImGui::IsMouseDoubleClicked(0)){
      this->double_click(path, item);
    }
  }

  //---------------------------
}

//Subfunction
void Selection::control_selection(utl::gui::navigator::Item& item, bool& already_selected){
  ImGuiIO& io = ImGui::GetIO();
  //---------------------------

  if(io.KeyCtrl){
    if(already_selected){
      this->vec_selection.find_erase_unsorted(item.ID);
    }
    else{
      this->vec_selection.push_back(item.ID);
    }
  }else{
    this->clear_selection();
    this->vec_selection.push_back(item.ID);
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
    this->vec_selection.push_back(item.ID);
    this->item_operation();
  }

  //---------------------------
}
void Selection::clear_selection(){
  //---------------------------

  this->vec_selection.clear();

  //---------------------------
}
void Selection::item_operation(){
  //---------------------------

  if(!nav_struct->fct_item_operation){
    std::cerr << "[error] No function set in Navigator" << std::endl;
    return;
  }

  nav_struct->fct_item_operation();
  this->clear_selection();

  //---------------------------
}

}
