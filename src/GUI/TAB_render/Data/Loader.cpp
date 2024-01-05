#include "Loader.h"

#include <Node/GUI.h>
#include <Engine/Engine.h>
#include <GUI/GUI_main/Interface/Tab.h>
#include <Engine/Data/Namespace.h>
#include <image/IconsFontAwesome6.h>
#include <Utility/Function/File/Info.h>


namespace gui::rnd::data{

//Constructor / Destructor
Loader::Loader(GUI* gui, bool* show_window, string name) : Panel(show_window, name){
  //---------------------------

  Engine* engine = gui->get_engine();
  eng::data::Node* eng_data = engine->get_eng_data();

  this->eng_scene = eng_data->get_eng_scene();
  this->eng_loader = eng_data->get_eng_loader();
  this->transformManager = new eng::ope::Transformation();
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

//Panel
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
    int ID = 0;
    vec_item_folder.clear();
    vec_item_file.clear();
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
        item.color_text = ImVec4(1.0f, 1.0f, 1.0f, 0.9f);
        vec_item_folder.push_back(item);
      }else if(item.type == "file"){
        item.path = file;
        item.name = info::get_name_from_path(file);
        item.icon = string(ICON_FA_FILE);
        item.size = info::get_file_formatted_size(file);
        item.weight = info::get_file_size(file);
        item.format = info::get_format_from_path(file);
        item.color_icon = ImVec4(1.0f, 1.0f, 1.0f, 0.9f);
        item.color_text = eng_loader->check_format_viability(item.format) ? ImVec4(0.0f, 1.0f, 1.0f, 0.9f) : ImVec4(1.0f, 1.0f, 1.0f, 0.9f);
        vec_item_file.push_back(item);
      }
    }

    // Sort data
    if(ImGuiTableSortSpecs* sort_specs = ImGui::TableGetSortSpecs()){
      Item::SortWithSortSpecs(sort_specs, vec_item_folder);
      Item::SortWithSortSpecs(sort_specs, vec_item_file);
    }

    // Populate the table - Folder
    ImGuiSelectableFlags flags;
    flags |= ImGuiSelectableFlags_SpanAllColumns;
    flags |= ImGuiSelectableFlags_AllowOverlap;
    flags |= ImGuiSelectableFlags_AllowDoubleClick;
    for(int i=0; i<vec_item_folder.size(); i++){
      Item& item = vec_item_folder[i];

      ImGui::TableNextColumn();
      ImGui::TextColored(item.color_icon, "%s", item.icon.c_str());
      ImGui::SameLine();
      ImGui::TextColored(item.color_text, "%s", item.name.c_str());
      ImGui::TableNextColumn();
      ImGui::TextColored(item.color_text, "%s", item.format.c_str());
      ImGui::TableNextColumn();
      ImGui::TextColored(item.color_text, "%s", item.size.c_str());

      //Selection stuff
      ImGui::SameLine();
      string name = "##" + to_string(item.ID);
      if(ImGui::Selectable(name.c_str(), false, flags) && ImGui::IsMouseDoubleClicked(0)){
        if(item.name == ".."){
          std::filesystem::path path = this->current_dir;
          this->current_dir = path.parent_path();
          this->file_selection.clear();
        }else{
          this->current_dir += "/" + item.name;
          this->file_selection.clear();
        }
      }
    }

    // Populate the table - File
    for(int i=0; i<vec_item_file.size(); i++){
      Item& item = vec_item_file[i];

      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      ImGui::TextColored(item.color_icon, "%s", item.icon.c_str());
      ImGui::SameLine();
      ImGui::TextColored(item.color_text, "%s", item.name.c_str());
      ImGui::TableNextColumn();
      ImGui::TextColored(item.color_text, "%s", item.format.c_str());
      ImGui::TableNextColumn();
      ImGui::TextColored(item.color_text, "%s", item.size.c_str());

      //Selection stuff
      ImGui::SameLine();
      const bool item_is_selected = file_selection.contains(item.ID);
      string name = "##" + to_string(item.ID);
      if (ImGui::Selectable(name.c_str(), item_is_selected, flags)){
        //Add selection to list
        if (ImGui::GetIO().KeyCtrl){
            if (item_is_selected){
              file_selection.find_erase_unsorted(item.ID);
            }
            else{
              file_selection.push_back(item.ID);
            }
        }else{
          file_selection.clear();
          file_selection.push_back(item.ID);
        }

        //If double clicked, load it
        if(ImGui::IsMouseDoubleClicked(0)){
          file_selection.clear();
          file_selection.push_back(item.ID);
          this->operation_load();
        }
      }
    }

    ImGui::EndTable();
  }

  //---------------------------
}
void Loader::draw_footer(){
  //---------------------------

  ImVec2 window_pos = ImGui::GetWindowPos();
  ImVec2 window_size = ImGui::GetWindowSize();
  float padding = file_selection.Size != 0 ? 40 : 20;
  ImGui::SetNextWindowPos(ImVec2(window_pos.x, window_size.y - padding), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(window_size.x, 100), ImGuiCond_Always);

  // Begin the footer window
  ImGuiWindowFlags flags;
  flags |= ImGuiWindowFlags_NoMove;
  flags |= ImGuiWindowFlags_NoTitleBar;
  flags |= ImGuiWindowFlags_NoResize;
  flags |= ImGuiWindowFlags_AlwaysAutoResize;
  flags |= ImGuiWindowFlags_NoSavedSettings;
  flags |= ImGuiWindowFlags_NoFocusOnAppearing;
  flags |= ImGuiWindowFlags_NoNav;
  flags |= ImGuiWindowFlags_NoNavFocus;
  flags |= ImGuiWindowFlags_NoScrollbar;
  flags |= ImGuiWindowFlags_NoDocking;
  ImGui::Begin("Footer", nullptr, flags);

  // Load button
  if(file_selection.Size != 0){
    if(ImGui::Button("Load##222")){
      this->operation_load();
      this->file_selection.clear();
    }
  }

  // Point cloud scaling
  ImGui::Separator();
  ImGui::SetNextItemWidth(100);
  ImGui::DragFloat("Scale##4567", &param_scaling, 0.1, 0.1, 100, "%.2f x");
  ImGui::SameLine();

  // Remove old clouds
  ImGui::Checkbox("Remove##222", &param_remove_old);

  // End the footer window
  ImGui::End();

  //---------------------------
}

//Subfunction
void Loader::operation_load(){
  //---------------------------

  //Retrieve all good selected files to load
  vector<string> vec_path;
  for(int i=0; i<vec_item_file.size(); i++){
    Item& item = vec_item_file[i];
    if(file_selection.contains(item.ID)){
      if(eng_loader->check_format_viability(item.format)){
        vec_path.push_back(item.path);
      }
    }
  }
  if(vec_path.size() == 0) return;

  //Apply loading and operations
  if(param_remove_old){
    eng_scene->delete_object_scene_all();
  }

  for(int i=0; i<vec_path.size(); i++){
    eng::structure::Object* object = eng_loader->load_object(vec_path[i]);
    if(object != nullptr){
      transformManager->make_scaling(object, param_scaling);
    }
  }

  //---------------------------
}

}
