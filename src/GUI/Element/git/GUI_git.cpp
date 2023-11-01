#include "GUI_git.h"

#include <GUI.h>
#include <Git/Git.h>



//Constructor / Destructor
GUI_git::GUI_git(GUI* gui){
  //---------------------------

  this->git = new Git();

  //---------------------------
}
GUI_git::~GUI_git(){}

//Main function
void GUI_git::design_panel(){
  //---------------------------

  this->draw_branches();

  //---------------------------
}

//Subfunction
void GUI_git::draw_branches(){
  vector<pair<string, string>> vec_branch = git->get_vec_branch_formatted();
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f,0.4f,0.4f,1.0f), "Branches");

  ImGuiTableFlags flags;
  flags |= ImGuiTableFlags_Borders;
  flags |= ImGuiTableFlags_RowBg;

  if(ImGui::BeginTable("git_table", 2, flags)){

    for(int i=0; i<vec_branch.size(); i++){
      pair<string, string> branch = vec_branch[i];

      ImGui::TableNextRow();

      ImGui::TableNextColumn();
      ImGui::Text("%s", branch.first.c_str());

      ImGui::TableNextColumn();
      ImGui::Text("%s", branch.second.c_str());
    }

    ImGui::EndTable();
  }

  //---------------------------
}
