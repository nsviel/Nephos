#include "Organisation.h"

#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace utl::gui::navigator{

//Constructor / Destructor
Organisation::Organisation(utl::gui::navigator::Structure* nav_struct){
  //---------------------------

  this->nav_struct = nav_struct;

  //---------------------------
}
Organisation::~Organisation(){}

//Main function
void Organisation::update_item_list(utl::base::Path& path){
  //---------------------------

  //Get current directory items
  if(curr_dir != path.directory){
    this->recolt_items(path.directory);
    curr_dir = path.directory;
  }

  //Sort items
  this->sort_items();

  //---------------------------
}

//Subfunction
void Organisation::recolt_items(std::string& directory){
  std::vector<std::string> vec_path = utl::path::list_all_path(directory);
  //---------------------------

  //Item vectors
  this->vec_file.clear();
  this->vec_folder.clear();

  //Insert items
  int ID = 0;
  for(int i=0; i<vec_path.size(); i++){
    std::string current_path = vec_path[i];
    if(is_hidden_file(current_path)) continue;

    if(utl::directory::is_directory(current_path)){
      this->insert_folder(vec_folder, current_path, ID);
    }else{
      this->insert_file(vec_file, current_path, ID);
    }
  }

  //---------------------------
}
void Organisation::sort_items(){
  //---------------------------

  //Sort items
  if(ImGuiTableSortSpecs* sort_specs = ImGui::TableGetSortSpecs()){
    utl::gui::navigator::File::sort_file_by_specs(sort_specs, vec_folder);
    utl::gui::navigator::File::sort_file_by_specs(sort_specs, vec_file);
  }

  //Copy items
  nav_struct->vec_item.clear();
  std::copy(vec_folder.begin(), vec_folder.end(), std::back_inserter(nav_struct->vec_item));
  std::copy(vec_file.begin(), vec_file.end(), std::back_inserter(nav_struct->vec_item));

  //---------------------------
}
void Organisation::insert_file(std::vector<utl::gui::navigator::File>& vec_item, std::string& path, int& ID){
  //---------------------------

  utl::gui::navigator::File file;
  file.item.ID = ID++;
  file.item.type = utl::gui::navigator::FILE;
  file.item.path = path;
  file.item.name = utl::path::get_name_from_path(path);
  file.item.icon = std::string(ICON_FA_FILE);
  file.item.size = utl::file::formatted_size(path);
  file.item.weight = utl::file::size(path);
  file.item.format = utl::path::get_format_from_path(path);
  file.item.color_icon = glm::vec4(1.0f, 1.0f, 1.0f, 0.9f);
  file.item.color_text = glm::vec4(1.0f, 1.0f, 1.0f, 0.9f);

  vec_item.push_back(file);

  //---------------------------
}
void Organisation::insert_folder(std::vector<utl::gui::navigator::File>& vec_item, std::string& path, int& ID){
  //---------------------------

  utl::gui::navigator::File file;
  file.item.ID = ID++;
  file.item.type = utl::gui::navigator::FOLDER;
  file.item.name = utl::path::get_filename_from_path(path);
  file.item.path = path;
  file.item.icon = std::string(ICON_FA_FOLDER);
  file.item.size = "---";
  file.item.weight = 0;
  file.item.format = "---";
  file.item.color_icon = glm::vec4(0.5f, 0.63f, 0.75f, 0.9f);
  file.item.color_text = glm::vec4(1.0f, 1.0f, 1.0f, 0.9f);

  vec_item.push_back(file);

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
