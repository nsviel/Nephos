#include "Logic.h"

#include <GUI/Namespace.h>
#include <Utility/Namespace.h>
#include <imgui/core/imgui.h>
#include <nlohmann/json.hpp>
#include <iostream>


namespace gui::state{

//Constructor / Destructor
Logic::Logic(gui::state::Structure* gui_struct){
  //---------------------------

  this->gui_struct = gui_struct;

  //---------------------------
}
Logic::~Logic(){}

//Main function
void Logic::update_list_file(){
  //---------------------------

  gui_struct->vec_file = utl::path::list_all_file(gui_struct->path_current.directory);

  //---------------------------
}
void Logic::make_current_default(){
  //---------------------------

  std::string path = gui_struct->path_default.build();
  //gui_io->state_save();

  //---------------------------
}
int Logic::get_idx_path_current(){
  int idx = -1;
  //---------------------------

  for(int i=0; i<gui_struct->vec_file.size(); i++){
    std::string& filename = gui_struct->vec_file[i];
    if(gui_struct->path_current.filename() == filename){
      return i;
    }
  }

  //---------------------------
  return idx;
}

}
