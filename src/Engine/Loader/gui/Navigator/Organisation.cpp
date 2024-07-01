#include "Organisation.h"

#include <Loader/Namespace.h>
#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace ldr::gui::navigator{

//Constructor / Destructor
Organisation::Organisation(ldr::gui::navigator::Structure* nav_struct){
  //---------------------------

  this->nav_struct = nav_struct;

  //---------------------------
}
Organisation::~Organisation(){}

//Main function
void Organisation::recolt_items(utl::base::Path& path){
  std::vector<std::string> vec_path = utl::path::list_all_path(path.directory);
  //---------------------------

  //Clear vectors
  nav_struct->vec_folder.clear();
  nav_struct->vec_file.clear();
  nav_struct->vec_item.clear();

  //Organize files
  int ID = 0;
  for(int i=0; i<vec_path.size(); i++){
    std::string current_path = vec_path[i];
    if(is_hidden_file(current_path)) continue;

    if(utl::directory::is_directory(current_path)){
      this->insert_folder(current_path, ID);
    }else{
      this->insert_file(current_path, ID);
    }
  }

  //---------------------------
}
void Organisation::sort_items(){
  //---------------------------

  //Sort both vectors
  if(ImGuiTableSortSpecs* sort_specs = ImGui::TableGetSortSpecs()){
    ldr::gui::navigator::File::sort_file_by_specs(sort_specs, nav_struct->vec_folder);
    ldr::gui::navigator::File::sort_file_by_specs(sort_specs, nav_struct->vec_file);
  }

  //Insert folders
  for(int i=0; i<nav_struct->vec_folder.size(); i++){
    nav_struct->vec_item.push_back(nav_struct->vec_folder[i]);
  }

  //Insert files
  for(int i=0; i<nav_struct->vec_file.size(); i++){
    nav_struct->vec_item.push_back(nav_struct->vec_file[i]);
  }

  //---------------------------
}

//Subfunction
void Organisation::insert_file(std::string& path, int& ID){
  //---------------------------

  ldr::gui::navigator::File file;
  file.item.ID = ID++;
  file.item.type = ldr::bookmark::FILE;
  file.item.path = path;
  file.item.name = utl::path::get_name_from_path(path);
  file.item.icon = std::string(ICON_FA_FILE);
  file.item.size = utl::file::formatted_size(path);
  file.item.weight = utl::file::size(path);
  file.item.format = utl::path::get_format_from_path(path);
  file.item.color_icon = glm::vec4(1.0f, 1.0f, 1.0f, 0.9f);
  file.item.color_text = glm::vec4(1.0f, 1.0f, 1.0f, 0.9f);

  nav_struct->vec_file.push_back(file);

  //---------------------------
}
void Organisation::insert_folder(std::string& path, int& ID){
  //---------------------------

  ldr::gui::navigator::File file;
  file.item.ID = ID++;
  file.item.type = ldr::bookmark::FOLDER;
  file.item.name = utl::path::get_filename_from_path(path);
  file.item.path = path;
  file.item.icon = std::string(ICON_FA_FOLDER);
  file.item.size = "---";
  file.item.weight = 0;
  file.item.format = "---";
  file.item.color_icon = glm::vec4(0.5f, 0.63f, 0.75f, 0.9f);
  file.item.color_text = glm::vec4(1.0f, 1.0f, 1.0f, 0.9f);

  nav_struct->vec_folder.push_back(file);

  //---------------------------
}
bool Organisation::is_hidden_file(std::string& path){
  //---------------------------

  std::string filename = utl::path::get_filename_from_path(path);
  if(filename[0] == '.' && filename[1] != '.') return true;

  //---------------------------
  return false;
}

}
