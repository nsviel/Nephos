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
void Selection::selection_item(utl::base::Path& path, ldr::gui::navigator::File& file){
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

    //Double click
    if(ImGui::IsMouseDoubleClicked(0)){
      this->double_click(path, file);
    }
  }

  //---------------------------
}

//Subfunction
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
    this->clear_selection();
    nav_struct->vec_selection.push_back(file.item.ID);
  }

  //---------------------------
}
void Selection::double_click(utl::base::Path& path, ldr::gui::navigator::File& file){
  //---------------------------

  if(file.item.type == ldr::bookmark::FOLDER){
    if(file.item.name == ".."){
      if(path.directory != "/home/") path.directory = utl::path::get_parent_path(path.directory);
      this->clear_selection();
    }else{
      std::string item_name = file.item.name;
      if(file.item.type == ldr::bookmark::FOLDER) item_name += "/";
      path.directory += item_name;
      this->clear_selection();
    }
  }else{
    this->clear_selection();
    nav_struct->vec_selection.push_back(file.item.ID);
    this->call_function();
  }

  //---------------------------
}
void Selection::clear_selection(){
  //---------------------------

  nav_struct->vec_selection.clear();

  //---------------------------
}

//External function
void Selection::add_function(std::function<void()> func){
  //---------------------------

  this->fct_item_operation = func;

  //---------------------------
}
void Selection::call_function(){
  //---------------------------

  if(!fct_item_operation){
    std::cerr << "No function set in Navigator!" << std::endl;
    return;
  }

  this->fct_item_operation();
  this->clear_selection();

  //---------------------------
}

}
