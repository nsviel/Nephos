#include "Organisation.h"

#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace utl::gui::navigator{

//Constructor / Destructor
Organisation::Organisation(utl::gui::Navigator* navigator){
  //---------------------------

  this->nav_struct = navigator->get_nav_struct();

  //---------------------------
}
Organisation::~Organisation(){}

//Main function
void Organisation::update_item_list(utl::base::Path& path){
  //---------------------------

  //Get current directory items
  /*if(curr_dir != path.directory){
    this->recolt_items(path.directory);
    curr_dir = path.directory;
  }*/
  this->recolt_items(path.directory);

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
    std::string& path = vec_path[i];
    if(is_hidden_file(path)) continue;

    if(utl::directory::is_directory(path)){
      this->insert_folder(vec_folder, path, ID);
    }else{
      this->insert_file(vec_file, path, ID);
    }
  }

  //---------------------------
}
void Organisation::sort_items(){
  //---------------------------

  //Sort items
  if(ImGuiTableSortSpecs* sort_specs = ImGui::TableGetSortSpecs()){
    utl::gui::navigator::Sorting::sort_file_by_specs(sort_specs, vec_folder);
    utl::gui::navigator::Sorting::sort_file_by_specs(sort_specs, vec_file);
  }

  //Copy items
  nav_struct->vec_item.clear();
  std::copy(vec_folder.begin(), vec_folder.end(), std::back_inserter(nav_struct->vec_item));
  std::copy(vec_file.begin(), vec_file.end(), std::back_inserter(nav_struct->vec_item));

  //---------------------------
}
void Organisation::insert_file(std::vector<utl::gui::navigator::Item>& vec_item, std::string& path, int& ID){
  //---------------------------

  utl::gui::navigator::Item item;
  item.ID = ID++;
  item.type = utl::gui::navigator::FILE;
  item.path = path;
  item.name = utl::path::get_name_from_path(path);
  item.icon = std::string(ICON_FA_FILE);
  item.size = utl::file::formatted_size(path);
  item.weight = utl::file::size(path);
  item.format = utl::path::get_format_from_path(path);
  item.color_icon = glm::vec4(1.0f, 1.0f, 1.0f, 0.9f);
  item.color_text = glm::vec4(1.0f, 1.0f, 1.0f, 0.9f);

  vec_item.push_back(item);

  //---------------------------
}
void Organisation::insert_folder(std::vector<utl::gui::navigator::Item>& vec_item, std::string& path, int& ID){
  //---------------------------

  utl::gui::navigator::Item item;
  item.ID = ID++;
  item.type = utl::gui::navigator::FOLDER;
  item.name = utl::path::get_filename_from_path(path);
  item.path = path + "/";
  item.icon = std::string(ICON_FA_FOLDER);
  item.size = "---";
  item.weight = 0;
  item.format = "---";
  item.color_icon = glm::vec4(0.5f, 0.63f, 0.75f, 0.9f);
  item.color_text = glm::vec4(1.0f, 1.0f, 1.0f, 0.9f);

  vec_item.push_back(item);

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
