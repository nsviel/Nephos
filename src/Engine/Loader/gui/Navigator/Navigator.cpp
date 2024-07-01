#include "Navigator.h"

#include <Loader/Namespace.h>
#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace ldr::gui{

//Constructor / Destructor
Navigator::Navigator(ldr::Node* node_loader){
  //---------------------------

  this->ldr_struct = node_loader->get_ldr_struct();
  this->ldr_importer = node_loader->get_ldr_importer();
  this->ldr_bookmark = node_loader->get_ldr_bookmark();

  this->with_bookmark = with_bookmark;
  this->default_path = utl::path::get_current_parent_path_abs();

  //---------------------------
}
Navigator::~Navigator(){}

//Main function
void Navigator::draw_navigator(utl::base::Path& path){
  //---------------------------

  this->draw_header(path);
  this->draw_file_content(path);

  //---------------------------
}

//Subfunction
void Navigator::draw_header(utl::base::Path& path){
  //---------------------------

  ImGui::BeginTable("header##recorder", 2);
  ImGui::TableSetupColumn("1", ImGuiTableColumnFlags_WidthStretch);
  ImGui::TableSetupColumn("2", ImGuiTableColumnFlags_WidthFixed, 25.0f);

  //Reset current dir
  ImGui::TableNextRow(); ImGui::TableNextColumn();
  if(ImGui::Button(ICON_FA_HOUSE "##222")){
    path.directory = default_path;
  }
  ImGui::SameLine();
  ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
  ImGui::SameLine();

  // Split the path into individual elements
  size_t start = 0;
  size_t end = path.directory.find_first_of('/');
  std::vector<std::string> pathElements;
  while(end != std::string::npos){
    pathElements.push_back(path.directory.substr(start, end - start));
    start = end + 1;
    end = path.directory.find_first_of('/', start);
  }

  // Add the last element (file/directory name)
  pathElements.push_back(path.directory.substr(start));

  // Render buttons for each path element
  std::string element_path;
  for(int i = 0; i < pathElements.size(); ++i){
    std::string element = pathElements[i];
    if(element == "") continue;

    ImGui::SameLine(0, 2);
    ImGui::Text("/");
    ImGui::SameLine(0, 2);

    ImGui::PushID(i);
    element_path += "/" + element;
    if(ImGui::Button(element.c_str())){
      path.directory = element_path + "/";
    }
    ImGui::PopID();
  }

  //Add folder button
  ImGui::TableNextColumn();
  if(ImGui::Button(ICON_FA_FOLDER_PLUS "##addfolder")){
    ImGui::OpenPopup("my_select_popup");
  }
  ImGui::SameLine();
  if(ImGui::BeginPopup("my_select_popup")){
    ImGui::Text("Folder name");

    static char str_n[256];
    ImGui::SetNextItemWidth(125);
    if(ImGui::InputText("##addfolder", str_n, IM_ARRAYSIZE(str_n), ImGuiInputTextFlags_EnterReturnsTrue)){
      std::string path_new_dir = path.directory + "/" + (std::string)str_n;
      utl::directory::create(path_new_dir);
      ImGui::CloseCurrentPopup();
    }
    ImGui::SameLine();
    if(ImGui::Button("Create##addfolder")){
      std::string path_new_dir = path.directory + "/" + (std::string)str_n;
      utl::directory::create(path_new_dir);
      ImGui::CloseCurrentPopup();
    }

    ImGui::EndPopup();
  }

  ImGui::EndTable();

  //---------------------------
}
void Navigator::draw_file_content(utl::base::Path& path){
  //---------------------------

  static ImGuiTableFlags flags;
  flags |= ImGuiTableFlags_BordersV;
  flags |= ImGuiTableFlags_BordersOuterH;
  flags |= ImGuiTableFlags_Resizable;
  flags |= ImGuiTableFlags_RowBg;
  flags |= ImGuiTableFlags_NoBordersInBody;
  flags |= ImGuiTableFlags_Sortable;
  ImGui::BeginTable("init_tree", 4, flags);
  // The first column will use the default _WidthStretch when ScrollX is Off and _WidthFixed when ScrollX is On
  ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthStretch | ImGuiTableColumnFlags_NoHide | ImGuiTableColumnFlags_DefaultSort, 175, ldr::bookmark::NAME);
  ImGui::TableSetupColumn("Format", ImGuiTableColumnFlags_WidthFixed, 75, ldr::bookmark::FORMAT);
  ImGui::TableSetupColumn("Size", ImGuiTableColumnFlags_WidthFixed, 75, ldr::bookmark::WEIGHT);
  ImGui::TableSetupColumn("##bookmark_1", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoResize, 20);
  ImGui::TableHeadersRow();

  std::vector<std::string> vec_path = utl::path::list_all_path(path.directory);
  this->item_filtering(vec_path);
  this->item_organisation(vec_path);
  this->item_folder(path);
  this->item_file(path);

  ImGui::EndTable();

  //---------------------------
}
void Navigator::draw_bookmark(ldr::gui::File& file){
  if(with_bookmark == false) return;
  //---------------------------

  //Button background if already bookmarked
  bool is_bookmarked = ldr_bookmark->is_path_bookmarked(file.item.path);
  int bg_alpha;
  is_bookmarked ? bg_alpha = 255 : bg_alpha = 0;

  //Draw bookmark button
  std::string ID = file.item.path + "##bookmarkbutton";
  ImGui::PushID(ID.c_str());
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(46, 133, 45, bg_alpha));
  ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(46, 133, 45, 0));
  if(ImGui::Button(ICON_FA_BOOKMARK "##addbookmark")){
    if(is_bookmarked){
      ldr_bookmark->remove_path(file.item.path);
    }else{
      ldr_bookmark->add_abs_path(file.item.path);
    }
    ldr_bookmark->save_on_file();
  }
  ImGui::PopStyleColor(2);
  ImGui::PopID();

  //---------------------------
}

//Item function
void Navigator::item_organisation(std::vector<std::string>& vec_path){
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
    ldr::gui::File::sort_file_by_specs(sort_specs, vec_folder);
    ldr::gui::File::sort_file_by_specs(sort_specs, vec_file);
  }

  //---------------------------
}
void Navigator::insert_file(std::string& path, int& ID){
  //---------------------------

  ldr::gui::File file;
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
void Navigator::insert_folder(std::string& path, int& ID){
  //---------------------------

  ldr::gui::File file;
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

void Navigator::item_folder(utl::base::Path& path){
  //---------------------------

  // Populate the table - Folder
  ImGuiSelectableFlags flags;
  flags |= ImGuiSelectableFlags_SpanAllColumns;
  flags |= ImGuiSelectableFlags_AllowOverlap;
  flags |= ImGuiSelectableFlags_AllowDoubleClick;
  for(int i=0; i<vec_folder.size(); i++){
    ldr::gui::File& file = vec_folder[i];

    ImGui::TableNextColumn();
    ImVec4 color_icon = ImVec4(file.item.color_icon.r, file.item.color_icon.g, file.item.color_icon.b, file.item.color_icon.a);
    ImGui::TextColored(color_icon, "%s", file.item.icon.c_str());
    ImGui::SameLine();
    ImVec4 color_text = ImVec4(file.item.color_text.r, file.item.color_text.g, file.item.color_text.b, file.item.color_text.a);
    ImGui::TextColored(color_text, "%s", file.item.name.c_str());
    ImGui::TableNextColumn();
    ImGui::TextColored(color_text, "%s", file.item.format.c_str());
    ImGui::TableNextColumn();
    ImGui::TextColored(color_text, "%s", file.item.size.c_str());
    ImGui::TableNextColumn();
    this->draw_bookmark(file);

    //Selection stuff
    ImGui::SameLine();
    bool item_is_selected = vec_selection.contains(file.item.ID);
    std::string name = "##" + std::to_string(file.item.ID);
    if(ImGui::Selectable(name.c_str(), item_is_selected, flags)){
      this->make_selection(file, item_is_selected);

      if(ImGui::IsMouseDoubleClicked(0)){
        if(file.item.name == ".."){
          std::filesystem::path fs_path = path.directory;
          path.directory = fs_path.parent_path();
          this->vec_selection.clear();
        }else{
          path.directory += "/" + file.item.name;
          this->vec_selection.clear();
        }
      }

    }
  }

  //---------------------------
}
void Navigator::item_file(utl::base::Path& path){
  //---------------------------

  // Populate the table - File
  ImGuiSelectableFlags flags;
  flags |= ImGuiSelectableFlags_SpanAllColumns;
  flags |= ImGuiSelectableFlags_AllowOverlap;
  flags |= ImGuiSelectableFlags_AllowDoubleClick;
  for(int i=0; i<vec_file.size(); i++){
    ldr::gui::File& file = vec_file[i];

    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImVec4 color_icon = ImVec4(file.item.color_icon.r, file.item.color_icon.g, file.item.color_icon.b, file.item.color_icon.a);
    ImGui::TextColored(color_icon, "%s", file.item.icon.c_str());
    ImGui::SameLine();
    ImVec4 color_text = ImVec4(file.item.color_text.r, file.item.color_text.g, file.item.color_text.b, file.item.color_text.a);
    ImGui::TextColored(color_text, "%s", file.item.name.c_str());
    ImGui::TableNextColumn();
    ImGui::TextColored(color_text, "%s", file.item.format.c_str());
    ImGui::TableNextColumn();
    ImGui::TextColored(color_text, "%s", file.item.size.c_str());
    ImGui::TableNextColumn();
    this->draw_bookmark(file);

    //Selection stuff
    ImGui::SameLine();
    bool item_is_selected = vec_selection.contains(file.item.ID);
    std::string name = "##" + std::to_string(file.item.ID);
    if(ImGui::Selectable(name.c_str(), item_is_selected, flags)){
      this->make_selection(file, item_is_selected);

      //If double clicked, load it
      if(ImGui::IsMouseDoubleClicked(0)){
        vec_selection.clear();
        vec_selection.push_back(file.item.ID);
        this->item_operation();
      }
    }
  }

  //---------------------------
}
void Navigator::make_selection(ldr::gui::File& file, bool& already_selected){
  ImGuiIO& io = ImGui::GetIO();
  //---------------------------

  if(io.KeyCtrl){
    if(already_selected){
      vec_selection.find_erase_unsorted(file.item.ID);
    }
    else{
      vec_selection.push_back(file.item.ID);
    }
  }else{
    vec_selection.clear();
    vec_selection.push_back(file.item.ID);
  }

  //---------------------------
}
void Navigator::item_selection(utl::base::Path& path){
  //---------------------------

  int selection = vec_selection[vec_selection.size() - 1];
  for(int i=0; i<vec_file.size(); i++){
    ldr::gui::File& file = vec_file[i];

    if(file.item.ID == selection){
      path.directory = utl::path::get_dir_from_path(file.item.path);
      path.name = utl::path::get_name_from_path(file.item.path);
      path.format = utl::path::get_format_from_path(file.item.path);
    }
  }

  //---------------------------
}

}
