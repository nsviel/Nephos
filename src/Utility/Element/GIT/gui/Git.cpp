#include "Git.h"

#include <fontawesome/IconsFontAwesome6.h>


namespace utl::element::gui{

//Constructor / Destructor
Git::Git(){
  //---------------------------

  //this->gui_font = gui->get_gui_font();
  this->git = new utl::element::Git();

  //---------------------------
}
Git::~Git(){}

//Main function
void Git::design_panel(){
  //---------------------------

  this->draw_information();
  this->draw_branches();

  //---------------------------
}

//Subfunction
void Git::draw_information(){
  //---------------------------

  //Print last tag
  string last_tag = git->get_last_tag();
  ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "v%s", last_tag.c_str());
  ImGui::SameLine();
  //ImFont* font_small = gui_font->get_font_small();
  //ImGui::PushFont(font_small);
  if(ImGui::Button(ICON_FA_PLUS)){
    git->up_tag_version();
  }
  //ImGui::PopFont();

  //---------------------------
}
void Git::draw_branches(){
  vector<pair<string, std::string>> vec_branch = git->get_vec_branch_formatted();
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f,0.4f,0.4f,1.0f), "Branches");

  ImGuiTableFlags flags;
  flags |= ImGuiTableFlags_Borders;
  flags |= ImGuiTableFlags_RowBg;

  ImGui::BeginTable("git_table", 2, flags);

  for(int i=0; i<vec_branch.size(); i++){
    pair<string, std::string> branch = vec_branch[i];

    ImGui::TableNextRow();

    ImGui::TableNextColumn();
    ImGui::Text("%s", branch.first.c_str());

    ImGui::TableNextColumn();
    ImGui::Text("%s", branch.second.c_str());
  }

  ImGui::EndTable();

  //---------------------------
}

}
