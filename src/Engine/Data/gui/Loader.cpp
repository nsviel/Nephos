#include "Loader.h"

#include <Engine/Data/Namespace.h>
#include <Engine/Operation/src/Namespace.h>
#include <Utility/Function/File/Info.h>
#include <image/IconsFontAwesome6.h>


namespace eng::scene::gui{

//Constructor / Destructor
Loader::Loader(eng::scene::Node* sce_node, bool* show_window){
  //---------------------------

  this->sce_scene = sce_node->get_scene();
  this->sce_loader = sce_node->get_scene_loader();
  this->sce_bookmark = sce_node->get_scene_bookmark();
  this->ope_transform = new eng::ope::Transformation();
  this->ope_operation = new eng::ope::Operation();

  this->default_dir = file::get_current_parent_path_abs();
  this->current_dir = default_dir;
  this->name = "Loader";
  this->show_window = show_window;

  //---------------------------
}
Loader::~Loader(){}

//Main function
void Loader::run_panel(){
  //---------------------------

  if(*show_window){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){

      this->design_panel();

      ImGui::End();
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Loader::design_panel(){
  ImGuiTabItemFlags flag = 0;
  //---------------------------

  if(goto_file_tab){
    flag = ImGuiTabItemFlags_SetSelected;
    this->goto_file_tab = false;
  }

  ImVec2 size = ImGui::GetContentRegionAvail();
  if(ImGui::BeginTabBar("Loader_tab##4567")){
    //File manager loader
    ImGui::SetNextItemWidth(size.x/2);
    if(ImGui::BeginTabItem("File##50", NULL, flag)){
      this->draw_file();
      ImGui::EndTabItem();
    }

    //Bookmark loader
    ImGui::SetNextItemWidth(size.x/2);
    if(ImGui::BeginTabItem("Bookmark##50", NULL)){
      this->draw_bookmark_tab();
      ImGui::EndTabItem();
    }

    ImGui::EndTabBar();
  }

  this->draw_footer();

  //---------------------------
}

//File stuff
void Loader::draw_file(){
  //---------------------------

  this->draw_file_header();
  this->draw_file_content();

  //---------------------------
}
void Loader::draw_file_header(){
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
void Loader::draw_file_content(){
  vector<string> vec_current_files = directory::list_all_path(current_dir);
  //---------------------------

  static ImGuiTableFlags flags;
  flags |= ImGuiTableFlags_BordersV;
  flags |= ImGuiTableFlags_BordersOuterH;
  flags |= ImGuiTableFlags_Resizable;
  flags |= ImGuiTableFlags_RowBg;
  flags |= ImGuiTableFlags_NoBordersInBody;
  flags |= ImGuiTableFlags_Sortable;
  if (ImGui::BeginTable("init_tree", 4, flags)){
    // The first column will use the default _WidthStretch when ScrollX is Off and _WidthFixed when ScrollX is On
    ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthStretch | ImGuiTableColumnFlags_NoHide | ImGuiTableColumnFlags_DefaultSort, 175, ColumnID_name);
    ImGui::TableSetupColumn("Format", ImGuiTableColumnFlags_WidthFixed, 75, ColumnID_format);
    ImGui::TableSetupColumn("Size", ImGuiTableColumnFlags_WidthFixed, 75, ColumnID_weight);
    ImGui::TableSetupColumn("##bookmark_1", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoResize, 20);
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
        item.path = file;
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
        item.color_text = sce_loader->is_format_supported(item.format) ? ImVec4(0.0f, 1.0f, 1.0f, 0.9f) : ImVec4(1.0f, 1.0f, 1.0f, 0.9f);
        vec_item_file.push_back(item);
      }
    }

    // Sort data
    if(ImGuiTableSortSpecs* sort_specs = ImGui::TableGetSortSpecs()){
      Item::sort_item_by_specs(sort_specs, vec_item_folder);
      Item::sort_item_by_specs(sort_specs, vec_item_file);
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
      ImGui::TableNextColumn();
      this->draw_bookmark_button(item);

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
      ImGui::TableNextColumn();
      this->draw_bookmark_button(item);

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
          this->operation_selection();
        }
      }
    }

    ImGui::EndTable();
  }

  //---------------------------
}

//Other stuff
void Loader::draw_bookmark_button(Item& item){
  //---------------------------

  //Button background if already bookmarked
  bool is_bookmarked = sce_bookmark->is_path_bookmarked(item.path);
  int bg_alpha;
  is_bookmarked ? bg_alpha = 255 : bg_alpha = 0;

  //Draw bookmark button
  string ID = item.path + "##bookmarkbutton";
  ImGui::PushID(ID.c_str());
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(46, 133, 45, bg_alpha));
  ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(46, 133, 45, 0));
  if(ImGui::Button(ICON_FA_BOOKMARK "##addbookmark")){
    if(is_bookmarked){
      sce_bookmark->remove_path(item.path);
    }else{
      sce_bookmark->add_abs_path(item.path);
    }
    sce_bookmark->save_on_file();
  }
  ImGui::PopStyleColor(2);
  ImGui::PopID();

  //---------------------------
}
void Loader::draw_bookmark_tab(){
  list<Item> list_bookmark = sce_bookmark->get_list_bookmark();
  //---------------------------

  for(int i=0; i<list_bookmark.size(); i++){
    Item& item = *next(list_bookmark.begin(), i);

    //File type icon
    ImGui::TextColored(item.color_icon, "%s", item.icon.c_str());

    //Bookmark name button
    ImGui::SameLine();
    int trash_space = 0;
    item.is_supressible ? trash_space = 30 : 0;
    int size = ImGui::GetContentRegionAvail().x - trash_space;
    ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.04, 0.5));
    if(ImGui::Button(item.name.c_str(), ImVec2(size, 0))){
      this->operation_selection(item.path);
    }
    ImGui::PopStyleVar();
    ImGui::SetItemTooltip("%s", item.path.c_str());

    //Bookmark supression
    if(item.is_supressible){
      ImGui::SameLine();
      string ID = item.path + "##supressionbookmark";
      ImGui::PushID(ID.c_str());
      if(ImGui::Button(ICON_FA_TRASH "##supressionbookmark")){
        sce_bookmark->remove_path(item.path);
        sce_bookmark->save_on_file();
      }
      ImGui::PopID();
    }
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
      this->operation_selection();
      this->file_selection.clear();
    }
  }

  // Scale new
  ImGui::Separator();
  ImGui::SetNextItemWidth(75);
  ImGui::DragFloat("Scale##4567", &param_scaling, 0.1, 0.1, 100, "%.2f x");

  // Remove old
  ImGui::SameLine();
  ImGui::Checkbox("Remove##222", &param_remove_old);

  // Center new
  ImGui::SameLine();
  ImGui::Checkbox("Centered##222", &param_centered);

  // End the footer window
  ImGui::End();

  //---------------------------
}

//Subfunction
void Loader::operation_selection(){
  //---------------------------

  //Retrieve all good selected files to load
  vector<string> vec_path;
  for(int i=0; i<vec_item_file.size(); i++){
    Item& item = vec_item_file[i];
    if(file_selection.contains(item.ID)){
      if(sce_loader->is_format_supported(item.format)){
        vec_path.push_back(item.path);
      }
    }
  }
  if(vec_path.size() == 0) return;

  //Apply loading and operations
  if(param_remove_old){
    utl::type::Set* set_scene = sce_scene->get_set_scene();
    set_scene->delete_entity_all();
  }

  for(int i=0; i<vec_path.size(); i++){
    utl::type::Entity* entity = sce_scene->import_entity(vec_path[i]);
    this->operation_entity(entity);
  }

  //---------------------------
}
void Loader::operation_selection(string path){
  //---------------------------

  if(directory::is_directory(path)){
    this->current_dir = path;
    this->goto_file_tab = true;
  }else{
    //File check
    string format = info::get_format_from_path(path);
    if(!file::is_file_exist(path)) return;
    if(!sce_loader->is_format_supported(format)) return;

    //Apply loading and operations
    if(param_remove_old){
      utl::type::Set* set_scene = sce_scene->get_set_scene();
      set_scene->delete_entity_all();
    }

    utl::type::Entity* entity = sce_scene->import_entity(path);
    this->operation_entity(entity);
  }

  //---------------------------
}
void Loader::operation_entity(utl::type::Entity* entity){
  //---------------------------


  if(entity != nullptr){
    //Scaling
    //ope_transform->make_scaling(object, param_scaling);

    //Centered
    if(param_centered){
      //ope_operation->center_object(object);
    }
  }

  //---------------------------
}


}
