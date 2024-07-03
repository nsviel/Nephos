#include "Logic.h"

#include <GUI/Namespace.h>
#include <Utility/Namespace.h>
#include <imgui/core/imgui.h>
#include <nlohmann/json.hpp>
#include <iostream>


namespace gui::state{

//Constructor / Destructor
Logic::Logic(gui::state::Manager* manager){
  //---------------------------

  this->sta_struct = manager->get_sta_struct();

  //---------------------------
}
Logic::~Logic(){}

//Main function
void Logic::update_list_file(){
  //---------------------------

  sta_struct->vec_file = utl::path::list_all_file(sta_struct->path_current.directory, ".json");

  //---------------------------
}
void Logic::make_current_default(){
  //---------------------------

  std::string path = sta_struct->path_default.build();
  //gui_io->state_save();

  //---------------------------
}
int Logic::get_idx_path_current(){
  int idx = -1;
  //---------------------------

  for(int i=0; i<sta_struct->vec_file.size(); i++){
    std::string& filename = sta_struct->vec_file[i];
    if(sta_struct->path_current.filename() == filename){
      return i;
    }
  }

  //---------------------------
  return idx;
}

}
