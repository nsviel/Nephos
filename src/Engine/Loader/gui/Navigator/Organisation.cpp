#include "Organisation.h"

#include <Loader/Namespace.h>
#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace ldr::gui::navigator{

//Constructor / Destructor
Organisation::Organisation(ldr::Node* node_loader){
  //---------------------------

  this->ldr_struct = node_loader->get_ldr_struct();
  this->ldr_importer = node_loader->get_ldr_importer();
  this->ldr_bookmark = node_loader->get_ldr_bookmark();

  this->with_bookmark = with_bookmark;
  this->default_path = utl::path::get_current_parent_path_abs();

  //---------------------------
}
Organisation::~Organisation(){}

//Main function
void Organisation::item_organisation(std::vector<std::string>& vec_path){
  //---------------------------

  //Item transposition
  int ID = 0;
  vec_folder.clear();
  vec_file.clear();
  for(int i=0; i<vec_path.size(); i++){
    std::string current_path = vec_path[i];
    std::string current_filename = utl::path::get_filename_from_path(current_path);
    //Remove hidden files
    if(current_filename[0] == '.' && current_filename[1] != '.') continue;

    //Get file info
    bool is_dir = utl::directory::is_directory(current_path);
    if(is_dir){
      this->insert_folder(current_path, ID);
    }else{
      this->insert_file(current_path, ID);
    }
  }

  // Sort data
  if(ImGuiTableSortSpecs* sort_specs = ImGui::TableGetSortSpecs()){
    ldr::gui::navigator::File::sort_file_by_specs(sort_specs, vec_folder);
    ldr::gui::navigator::File::sort_file_by_specs(sort_specs, vec_file);
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

  this->vec_file.push_back(file);

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

  this->vec_folder.push_back(file);

  //---------------------------
}

}
