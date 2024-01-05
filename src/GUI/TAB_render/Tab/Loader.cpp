#include "Loader.h"
#include "Item.h"

#include <Node/GUI.h>
#include <Engine/Engine.h>
#include <GUI/GUI_main/Interface/Tab.h>
#include <Engine/Data/Namespace.h>
#include <GUI/TAB_render/Tab/Init.h>
#include <imgui/dialog/ImDialog.h>
#include <image/IconsFontAwesome6.h>
#include <Utility/Function/File/Info.h>


namespace gui::rnd::tab{

//Constructor / Destructor
Loader::Loader(GUI* gui, bool* show_window, string name) : Panel(show_window, name){
  //---------------------------

  Engine* engine = gui->get_engine();
  eng::data::Node* eng_data = engine->get_eng_data();

  this->eng_loader = eng_data->get_eng_loader();
  this->default_dir = file::get_current_parent_path_abs();
  this->current_dir = default_dir;

  //---------------------------
}
Loader::~Loader(){}

//Main function
void Loader::design_panel(){
  //---------------------------

  this->draw_header();
  this->draw_content();
  this->draw_footer();

  //---------------------------
}

//Subfunction
void Loader::draw_header(){
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
  while (end != std::string::npos) {
    pathElements.push_back(current_dir.substr(start, end - start));
    start = end + 1;
    end = current_dir.find_first_of('/', start);
  }

  // Add the last element (file/directory name)
  pathElements.push_back(current_dir.substr(start));

  // Render buttons for each path element
  std::string element_path;
  for (int i = 0; i < pathElements.size(); ++i) {
    string element = pathElements[i];
    if(element == "") continue;

    ImGui::SameLine(0, 2);
    ImGui::Text("/");
    ImGui::SameLine(0, 2);

    ImGui::PushID(i);
    element_path += "/" + element;
    if (ImGui::Button(element.c_str())) {
      this->current_dir = element_path;
    }
    ImGui::PopID();
  }

  //---------------------------
}
void Loader::draw_content(){
  vector<string> vec_current_files = directory::list_all_path(current_dir);
  //---------------------------

  static ImGuiTableFlags flags;
  flags |= ImGuiTableFlags_BordersV;
  flags |= ImGuiTableFlags_BordersOuterH;
  flags |= ImGuiTableFlags_Resizable;
  flags |= ImGuiTableFlags_RowBg;
  flags |= ImGuiTableFlags_NoBordersInBody;
  flags |= ImGuiTableFlags_Sortable;
  if (ImGui::BeginTable("init_tree", 3, flags)){
    // The first column will use the default _WidthStretch when ScrollX is Off and _WidthFixed when ScrollX is On
    ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_NoHide | ImGuiTableColumnFlags_DefaultSort, 175, ColumnID_name);
    ImGui::TableSetupColumn("Format", ImGuiTableColumnFlags_WidthFixed, 75, ColumnID_format);
    ImGui::TableSetupColumn("Size", ImGuiTableColumnFlags_WidthFixed, 75, ColumnID_weight);
    ImGui::TableHeadersRow();

    //Item transposition
    vector<Item> vec_item_folder;
    vector<Item> vec_item_file;
    int ID = 0;
    for(int i=0; i<vec_current_files.size(); i++){
      Item item;
      string file = vec_current_files[i];
      string filename = info::get_filename_from_path(file);
      //Remove hidden files
      if(filename[0] == '.' && filename[1] != '.') continue;

      //Get file info
      item.ID = ID++;
      item.type = directory::is_dir_or_file(file);
      if(item.type == "directory"){
        item.name = info::get_filename_from_path(file);
        item.icon = string(ICON_FA_FOLDER);
        item.size = "---";
        item.weight = 0;
        item.format = "---";
        item.color_icon = ImVec4(0.5f, 0.63f, 0.75f, 0.9f);
        vec_item_folder.push_back(item);
      }else if(item.type == "file"){
        item.name = info::get_name_from_path(file);
        item.icon = string(ICON_FA_FILE);
        item.size = info::get_file_formatted_size(file);
        item.weight = info::get_file_size(file);
        item.format = info::get_format_from_path(file);
        item.color_icon = ImVec4(1.0f, 1.0f, 1.0f, 0.9f);
        vec_item_file.push_back(item);
      }
    }

    // Sort data
    if(ImGuiTableSortSpecs* sort_specs = ImGui::TableGetSortSpecs()){
      Item::SortWithSortSpecs(sort_specs, vec_item_folder);
      Item::SortWithSortSpecs(sort_specs, vec_item_file);
    }

    // Populate the table - Folder
    for(int i=0; i<vec_item_folder.size(); i++){
      Item& item = vec_item_folder[i];

      ImGui::TableNextRow();
      if (ImGui::IsMouseDoubleClicked(0) && ImGui::TableSetColumnIndex(-1)) {
        this->current_dir += "/" + item.name;
        std::cout << "Double-clicked on row: " << i << std::endl;
      }

      ImGui::TableNextColumn();
      ImGui::TextColored(item.color_icon, "%s", item.icon.c_str());
      ImGui::SameLine();
      ImGui::Text("%s", item.name.c_str());
      ImGui::TableNextColumn();
      ImGui::Text("%s", item.format.c_str());
      ImGui::TableNextColumn();
      ImGui::Text("%s", item.size.c_str());
    }

    // Populate the table - File
    static ImVector<int> selection;
    ImGuiSelectableFlags flags = ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowOverlap;
    for(int i=0; i<vec_item_file.size(); i++){
      Item& item = vec_item_file[i];

      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      ImGui::TextColored(item.color_icon, "%s", item.icon.c_str());
      ImGui::SameLine();
      const bool item_is_selected = selection.contains(item.ID);
      if (ImGui::Selectable(item.name.c_str(), item_is_selected, flags)){
        if (ImGui::GetIO().KeyCtrl){
            if (item_is_selected){
              selection.find_erase_unsorted(item.ID);
            }
            else{
              selection.push_back(item.ID);
            }
        }else{
          selection.clear();
          selection.push_back(item.ID);
        }
      }
      ImGui::TableNextColumn();
      ImGui::Text("%s", item.format.c_str());
      ImGui::TableNextColumn();
      ImGui::Text("%s", item.size.c_str());
    }

    ImGui::EndTable();
  }

  //---------------------------
}
void Loader::draw_footer(){
  //---------------------------

  //Point cloud scaling
  ImGui::SetNextItemWidth(100);
  ImGui::DragFloat("Scale##4567", &scale, 0.1, 0.1, 100, "%.2f x");
  ImGui::SameLine();

  //Remove old clouds
  ImGui::Checkbox("Remove##222", &remove_old);

  //---------------------------
}

}
