#include "Loader.h"

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
  this->current_dir = file::get_current_parent_path_abs();
  this->vec_current_files = directory::list_all_path(current_dir);

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

    ImGui::SameLine();
    ImGui::Text("/");
    ImGui::SameLine();

    ImGui::PushID(i);
    element_path += "/" + element;
    if (ImGui::Button(element.c_str())) {

      say(element_path);
    }
    ImGui::PopID();
  }

  //---------------------------
}
void Loader::draw_content(){
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
    ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_NoHide | ImGuiTableColumnFlags_DefaultSort, 175);
    ImGui::TableSetupColumn("Format", ImGuiTableColumnFlags_WidthFixed, 75);
    ImGui::TableSetupColumn("Size", ImGuiTableColumnFlags_WidthFixed, 75);
    ImGui::TableHeadersRow();

    for(int i=0; i<vec_current_files.size(); i++){
      string file = vec_current_files[i];
      string filename = info::get_filename_from_path(file);
      if(filename[0] == '.') continue;

      string name = info::get_name_from_path(file);
      string type = directory::is_dir_or_file(file);
      string format;
      string size;
      string icon;
      ImVec4 icon_color;

      if(type == "directory"){
        icon = string(ICON_FA_FOLDER);
        size = "---";
        format = "---";
        icon_color = ImVec4(0.5f, 0.63f, 0.75f, 0.9f);
      }else if(type == "file"){
        icon = string(ICON_FA_FILE);
        size = info::get_file_formatted_size(file);
        format = info::get_format_from_path(file);
        icon_color = ImVec4(1.0f, 1.0f, 1.0f, 0.9f);
      }


      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      ImGui::TextColored(icon_color, "%s", icon.c_str());
      ImGui::SameLine();
      ImGui::Text("%s", name.c_str());
      ImGui::TableNextColumn();
      ImGui::Text("%s", format.c_str());
      ImGui::TableNextColumn();
      ImGui::Text("%s", size.c_str());
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
