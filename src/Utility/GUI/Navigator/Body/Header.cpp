#include "Header.h"

#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace utl::gui::navigator{

//Constructor / Destructor
Header::Header(utl::gui::Navigator* navigator){
  //---------------------------

  this->nav_struct = navigator->get_nav_struct();

  //---------------------------
}
Header::~Header(){}

//Main function
void Header::draw_header(utl::base::Path& path){
  //---------------------------

  ImGui::BeginTable("header##recorder", 2);
  ImGui::TableSetupColumn("1", ImGuiTableColumnFlags_WidthStretch);
  ImGui::TableSetupColumn("2", ImGuiTableColumnFlags_WidthFixed, 25.0f);

  ImGui::TableNextRow(); ImGui::TableNextColumn();
  this->draw_directory_trail(path);

  ImGui::TableNextColumn();
  this->draw_directory_add(path);

  ImGui::EndTable();

  //---------------------------
}

//Subfunction
void Header::draw_directory_trail(utl::base::Path& path){
  //---------------------------

  //Reset current dir
  if(ImGui::Button(ICON_FA_HOUSE "##222")){
    path.directory = nav_struct->default_path;
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

  //---------------------------
}
void Header::draw_directory_add(utl::base::Path& path){
  //---------------------------

  //Add folder button
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

  //---------------------------
}

}
