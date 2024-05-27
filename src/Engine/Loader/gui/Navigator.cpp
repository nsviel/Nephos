#include "Navigator.h"

#include <Loader/Namespace.h>
#include <Utility/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace ldr::gui{

//Constructor / Destructor
Navigator::Navigator(ldr::Node* node_loader){
  //---------------------------

  this->ldr_importer = node_loader->get_ldr_importer();
  this->ldr_bookmark = node_loader->get_ldr_bookmark();

  this->default_dir = utl::path::get_current_parent_path_abs();
  this->current_dir = default_dir;

  //---------------------------
}
Navigator::~Navigator(){}

//Main function
void Navigator::draw_navigator(){
  //---------------------------

  this->draw_header();
  this->draw_file_content();

  //---------------------------
}

//Subfunction
void Navigator::draw_header(){
  //---------------------------

  //Reset current dir
  if(ImGui::Button(ICON_FA_HOUSE "##222")){
    this->current_dir = default_dir;
  }
  ImGui::SameLine();
  ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
  ImGui::SameLine();

  // Split the path into individual elements
  size_t start = 0;
  size_t end = current_dir.find_first_of('/');
  std::vector<std::string> pathElements;
  while (end != std::string::npos){
    pathElements.push_back(current_dir.substr(start, end - start));
    start = end + 1;
    end = current_dir.find_first_of('/', start);
  }

  // Add the last element (file/directory name)
  pathElements.push_back(current_dir.substr(start));

  // Render buttons for each path element
  std::string element_path;
  for (int i = 0; i < pathElements.size(); ++i){
    std::string element = pathElements[i];
    if(element == "") continue;

    ImGui::SameLine(0, 2);
    ImGui::Text("/");
    ImGui::SameLine(0, 2);

    ImGui::PushID(i);
    element_path += "/" + element;
    if(ImGui::Button(element.c_str())){
      this->current_dir = element_path;
    }
    ImGui::PopID();
  }

  //---------------------------
}
void Navigator::draw_file_content(){
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

  this->item_organisation();
  this->item_folder();
  this->item_file();

  ImGui::EndTable();

  //---------------------------
}
void Navigator::draw_bookmark(ldr::gui::Bookmark& bookmark){
  //---------------------------

  //Button background if already bookmarked
  bool is_bookmarked = ldr_bookmark->is_path_bookmarked(bookmark.item.path);
  int bg_alpha;
  is_bookmarked ? bg_alpha = 255 : bg_alpha = 0;

  //Draw bookmark button
  std::string ID = bookmark.item.path + "##bookmarkbutton";
  ImGui::PushID(ID.c_str());
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(46, 133, 45, bg_alpha));
  ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(46, 133, 45, 0));
  if(ImGui::Button(ICON_FA_BOOKMARK "##addbookmark")){
    if(is_bookmarked){
      ldr_bookmark->remove_path(bookmark.item.path);
    }else{
      ldr_bookmark->add_abs_path(bookmark.item.path);
    }
    ldr_bookmark->save_on_file();
  }
  ImGui::PopStyleColor(2);
  ImGui::PopID();

  //---------------------------
}

//Item function
void Navigator::item_organisation(){
  std::vector<std::string> vec_current_files = utl::path::list_all_path(current_dir);
  //---------------------------

  //Item transposition
  int ID = 0;
  vec_bookmark_folder.clear();
  vec_bookmark_file.clear();
  for(int i=0; i<vec_current_files.size(); i++){
    ldr::gui::Bookmark bookmark;
    std::string file = vec_current_files[i];
    std::string filename = utl::path::get_filename_from_path(file);
    //Remove hidden files
    if(filename[0] == '.' && filename[1] != '.') continue;

    //Get file info
    bookmark.item.ID = ID++;
    bookmark.item.type = utl::directory::is_directory(file) ? ldr::bookmark::FOLDER : ldr::bookmark::FILE;
    if(bookmark.item.type == ldr::bookmark::FOLDER){
      bookmark.item.name = utl::path::get_filename_from_path(file);
      bookmark.item.path = file;
      bookmark.item.icon = std::string(ICON_FA_FOLDER);
      bookmark.item.size = "---";
      bookmark.item.weight = 0;
      bookmark.item.format = "---";
      bookmark.item.color_icon = glm::vec4(0.5f, 0.63f, 0.75f, 0.9f);
      bookmark.item.color_text = glm::vec4(1.0f, 1.0f, 1.0f, 0.9f);
      vec_bookmark_folder.push_back(bookmark);
    }else if(bookmark.item.type == ldr::bookmark::FILE){
      bookmark.item.path = file;
      bookmark.item.name = utl::path::get_name_from_path(file);
      bookmark.item.icon = std::string(ICON_FA_FILE);
      bookmark.item.size = utl::file::formatted_size(file);
      bookmark.item.weight = utl::file::size(file);
      bookmark.item.format = utl::path::get_format_from_path(file);
      bookmark.item.color_icon = glm::vec4(1.0f, 1.0f, 1.0f, 0.9f);
      bookmark.item.color_text = ldr_importer->is_format_supported(bookmark.item.format) ? glm::vec4(0.0f, 1.0f, 1.0f, 0.9f) : glm::vec4(1.0f, 1.0f, 1.0f, 0.9f);
      vec_bookmark_file.push_back(bookmark);
    }
  }

  // Sort data
  if(ImGuiTableSortSpecs* sort_specs = ImGui::TableGetSortSpecs()){
    ldr::gui::Bookmark::sort_item_by_specs(sort_specs, vec_bookmark_folder);
    ldr::gui::Bookmark::sort_item_by_specs(sort_specs, vec_bookmark_file);
  }

  //---------------------------
}
void Navigator::item_folder(){
  //---------------------------

  // Populate the table - Folder
  ImGuiSelectableFlags flags;
  flags |= ImGuiSelectableFlags_SpanAllColumns;
  flags |= ImGuiSelectableFlags_AllowOverlap;
  flags |= ImGuiSelectableFlags_AllowDoubleClick;
  for(int i=0; i<vec_bookmark_folder.size(); i++){
    ldr::gui::Bookmark& bookmark = vec_bookmark_folder[i];

    ImGui::TableNextColumn();
    ImVec4 color_icon = ImVec4(bookmark.item.color_icon.r, bookmark.item.color_icon.g, bookmark.item.color_icon.b, bookmark.item.color_icon.a);
    ImGui::TextColored(color_icon, "%s", bookmark.item.icon.c_str());
    ImGui::SameLine();
    ImVec4 color_text = ImVec4(bookmark.item.color_text.r, bookmark.item.color_text.g, bookmark.item.color_text.b, bookmark.item.color_text.a);
    ImGui::TextColored(color_text, "%s", bookmark.item.name.c_str());
    ImGui::TableNextColumn();
    ImGui::TextColored(color_text, "%s", bookmark.item.format.c_str());
    ImGui::TableNextColumn();
    ImGui::TextColored(color_text, "%s", bookmark.item.size.c_str());
    ImGui::TableNextColumn();
    this->draw_bookmark(bookmark);

    //Selection stuff
    ImGui::SameLine();
    const bool item_is_selected = vec_selection.contains(bookmark.item.ID);
    std::string name = "##" + std::to_string(bookmark.item.ID);
    if(ImGui::Selectable(name.c_str(), item_is_selected, flags)){

      if(ImGui::IsMouseDoubleClicked(0)){
        if(bookmark.item.name == ".."){
          std::filesystem::path path = this->current_dir;
          this->current_dir = path.parent_path();
          this->vec_selection.clear();
        }else{
          this->current_dir += "/" + bookmark.item.name;
          this->vec_selection.clear();
        }
      }else{
        vec_selection.clear();
        vec_selection.push_back(bookmark.item.ID);
      }

    }
  }

  //---------------------------
}
void Navigator::item_file(){
  //---------------------------

  // Populate the table - File
  ImGuiSelectableFlags flags;
  flags |= ImGuiSelectableFlags_SpanAllColumns;
  flags |= ImGuiSelectableFlags_AllowOverlap;
  flags |= ImGuiSelectableFlags_AllowDoubleClick;
  for(int i=0; i<vec_bookmark_file.size(); i++){
    ldr::gui::Bookmark& bookmark = vec_bookmark_file[i];

    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImVec4 color_icon = ImVec4(bookmark.item.color_icon.r, bookmark.item.color_icon.g, bookmark.item.color_icon.b, bookmark.item.color_icon.a);
    ImGui::TextColored(color_icon, "%s", bookmark.item.icon.c_str());
    ImGui::SameLine();
    ImVec4 color_text = ImVec4(bookmark.item.color_text.r, bookmark.item.color_text.g, bookmark.item.color_text.b, bookmark.item.color_text.a);
    ImGui::TextColored(color_text, "%s", bookmark.item.name.c_str());
    ImGui::TableNextColumn();
    ImGui::TextColored(color_text, "%s", bookmark.item.format.c_str());
    ImGui::TableNextColumn();
    ImGui::TextColored(color_text, "%s", bookmark.item.size.c_str());
    ImGui::TableNextColumn();
    this->draw_bookmark(bookmark);

    //Selection stuff
    ImGui::SameLine();
    const bool item_is_selected = vec_selection.contains(bookmark.item.ID);
    std::string name = "##" + std::to_string(bookmark.item.ID);
    if(ImGui::Selectable(name.c_str(), item_is_selected, flags)){
      //Add selection to list
      if(ImGui::GetIO().KeyCtrl){
        if(item_is_selected){
          vec_selection.find_erase_unsorted(bookmark.item.ID);
        }
        else{
          vec_selection.push_back(bookmark.item.ID);
        }
      }else{
        vec_selection.clear();
        vec_selection.push_back(bookmark.item.ID);
      }

      //If double clicked, load it
      if(ImGui::IsMouseDoubleClicked(0)){
        vec_selection.clear();
        vec_selection.push_back(bookmark.item.ID);
        this->operation_selection();
      }
    }
  }

  //---------------------------
}

}
