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
void Selection::make_selection(ldr::gui::navigator::File& file, bool& already_selected){
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
void Selection::item_selection(utl::base::Path& path){
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

}
