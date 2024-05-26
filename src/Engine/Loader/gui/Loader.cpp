#include "Loader.h"

#include <Data/Namespace.h>
#include <Loader/Namespace.h>
#include <Operation/Namespace.h>
#include <Utility/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace ldr::gui{

//Constructor / Destructor
Loader::Loader(ldr::Node* node_loader, bool* show_window){
  //---------------------------

  dat::Node* node_data = node_loader->get_node_data();

  this->dat_graph = node_data->get_dat_graph();
  this->dat_set = node_data->get_data_set();
  this->ldr_importer = node_loader->get_ldr_importer();
  this->ldr_bookmark = node_loader->get_ldr_bookmark();
  this->ope_transform = new ope::Transformation();
  this->ope_operation = new ope::Operation();

  this->default_dir = utl::path::get_current_parent_path_abs();
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
    ImGui::SetNextWindowSizeConstraints(ImVec2(300, 300), ImVec2(400, FLT_MAX));
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

  this->draw_header();
  ImGui::Separator();

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
    std::string element = pathElements[i];
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
  std::vector<std::string> vec_current_files = utl::path::list_all_path(current_dir);
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
    ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthStretch | ImGuiTableColumnFlags_NoHide | ImGuiTableColumnFlags_DefaultSort, 175, ldr::item::NAME);
    ImGui::TableSetupColumn("Format", ImGuiTableColumnFlags_WidthFixed, 75, ldr::item::FORMAT);
    ImGui::TableSetupColumn("Size", ImGuiTableColumnFlags_WidthFixed, 75, ldr::item::WEIGHT);
    ImGui::TableSetupColumn("##bookmark_1", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoResize, 20);
    ImGui::TableHeadersRow();

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
      bookmark.item.type = utl::directory::is_directory(file) ? ldr::item::FOLDER : ldr::item::FILE;
      if(bookmark.item.type == ldr::item::FOLDER){
        bookmark.item.name = utl::path::get_filename_from_path(file);
        bookmark.item.path = file;
        bookmark.item.icon = std::string(ICON_FA_FOLDER);
        bookmark.item.size = "---";
        bookmark.item.weight = 0;
        bookmark.item.format = "---";
        bookmark.item.color_icon = glm::vec4(0.5f, 0.63f, 0.75f, 0.9f);
        bookmark.item.color_text = glm::vec4(1.0f, 1.0f, 1.0f, 0.9f);
        vec_bookmark_folder.push_back(bookmark);
      }else if(bookmark.item.type == ldr::item::FILE){
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
      this->draw_bookmark_button(bookmark);

      //Selection stuff
      ImGui::SameLine();
      const bool item_is_selected = file_selection.contains(bookmark.item.ID);
      std::string name = "##" + std::to_string(bookmark.item.ID);
      if(ImGui::Selectable(name.c_str(), item_is_selected, flags)){

        if(ImGui::IsMouseDoubleClicked(0)){
          if(bookmark.item.name == ".."){
            std::filesystem::path path = this->current_dir;
            this->current_dir = path.parent_path();
            this->file_selection.clear();
          }else{
            this->current_dir += "/" + bookmark.item.name;
            this->file_selection.clear();
          }
        }else{
          file_selection.clear();
          file_selection.push_back(bookmark.item.ID);
        }

      }
    }

    // Populate the table - File
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
      this->draw_bookmark_button(bookmark);

      //Selection stuff
      ImGui::SameLine();
      const bool item_is_selected = file_selection.contains(bookmark.item.ID);
      std::string name = "##" + std::to_string(bookmark.item.ID);
      if (ImGui::Selectable(name.c_str(), item_is_selected, flags)){
        //Add selection to list
        if(ImGui::GetIO().KeyCtrl){
          if (item_is_selected){
            file_selection.find_erase_unsorted(bookmark.item.ID);
          }
          else{
            file_selection.push_back(bookmark.item.ID);
          }
        }else{
          file_selection.clear();
          file_selection.push_back(bookmark.item.ID);
        }

        //If double clicked, load it
        if(ImGui::IsMouseDoubleClicked(0)){
          file_selection.clear();
          file_selection.push_back(bookmark.item.ID);
          this->operation_selection();
        }
      }
    }

    ImGui::EndTable();
  }

  //---------------------------
}

//Other stuff
void Loader::draw_bookmark_button(ldr::gui::Bookmark& bookmark){
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
void Loader::draw_bookmark_tab(){
  std::list<ldr::Item> list_item = ldr_bookmark->get_list_item();
  //---------------------------

  for(int i=0; i<list_item.size(); i++){
    ldr::Item& item = *next(list_item.begin(), i);
    ldr::gui::Bookmark bookmark;
    bookmark.item = item;

    //File type icon
    ImVec4 color_icon = ImVec4(bookmark.item.color_icon.r, bookmark.item.color_icon.g, bookmark.item.color_icon.b, bookmark.item.color_icon.a);
    ImGui::TextColored(color_icon, "%s", bookmark.item.icon.c_str());

    //Bookmark name button
    ImGui::SameLine();
    int trash_space = 0;
    bookmark.item.is_supressible ? trash_space = 30 : 0;
    int size = ImGui::GetContentRegionAvail().x - trash_space;
    ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.04, 0.5));
    if(ImGui::Button(bookmark.item.name.c_str(), ImVec2(size, 0))){
      this->operation_selection(bookmark.item.path);
    }
    ImGui::PopStyleVar();
    ImGui::SetItemTooltip("%s", bookmark.item.path.c_str());

    //Bookmark supression
    if(bookmark.item.is_supressible){
      ImGui::SameLine();
      std::string ID = bookmark.item.path + "##supressionbookmark";
      ImGui::PushID(ID.c_str());
      if(ImGui::Button(ICON_FA_TRASH "##supressionbookmark")){
        ldr_bookmark->remove_path(bookmark.item.path);
        ldr_bookmark->save_on_file();
      }
      ImGui::PopID();
    }
  }

  //---------------------------
}
void Loader::draw_header(){
  //---------------------------

  // Load button
  if(ImGui::Button("Load##222")){
    this->operation_selection();
    this->file_selection.clear();
  }

  // Scale new
  ImGui::SameLine();
  ImGui::SetNextItemWidth(75);
  ImGui::DragFloat("Scale##4567", &param_scaling, 0.1, 0.1, 100, "%.2f x");

  // Remove old
  ImGui::SameLine();
  ImGui::Checkbox("Remove##222", &param_remove_old);

  // Center new
  ImGui::SameLine();
  ImGui::Checkbox("Centered##222", &param_centered);

  //---------------------------
}

//Subfunction
void Loader::operation_selection(){
  //---------------------------

  //Retrieve all good selected files to load
  std::vector<std::string> vec_path;
  for(int i=0; i<vec_bookmark_file.size(); i++){
    ldr::gui::Bookmark& bookmark = vec_bookmark_file[i];
    if(file_selection.contains(bookmark.item.ID)){
      if(ldr_importer->is_format_supported(bookmark.item.format)){
        vec_path.push_back(bookmark.item.path);
      }
    }
  }
  if(vec_path.size() == 0) return;

  //Apply loading and operations
  if(param_remove_old){
    dat::base::Set* set_graph = dat_graph->get_set_graph();
    dat_set->remove_all_entity(set_graph);
  }

  for(int i=0; i<vec_path.size(); i++){
    utl::media::Path path;
    path.data = vec_path[i];

    dat::base::Object* object = ldr_importer->load_object(path);

    if(object != nullptr){
      this->operation_entity(object);
    }
  }

  //---------------------------
}
void Loader::operation_selection(std::string file_path){
  //---------------------------

  //If selection is a directory go display his content
  if(utl::directory::is_directory(file_path)){
    this->current_dir = file_path;
    this->goto_file_tab = true;
  }
  //If selection is a file go load it
  else{
    //File check
    std::string format = utl::path::get_format_from_path(file_path);
    if(!utl::file::is_exist(file_path)) return;
    if(!ldr_importer->is_format_supported(format)) return;

    //Apply loading and operations
    if(param_remove_old){
      dat::base::Set* set_graph = dat_graph->get_set_graph();
      dat_set->remove_all_entity(set_graph);
    }

    utl::media::Path path;
    path.data = file_path;
    dat::base::Object* object = ldr_importer->load_object(path);

    if(object != nullptr){
      this->operation_entity(object);
    }
  }

  //---------------------------
}
void Loader::operation_entity(dat::base::Entity* entity){
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
