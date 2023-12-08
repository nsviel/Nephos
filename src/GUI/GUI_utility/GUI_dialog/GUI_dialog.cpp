#include "GUI_dialog.h"

#include <GUI.h>
#include <imgui/dialog/ImGuiFileDialog.h>


//Constructor / Destructor
GUI_dialog::GUI_dialog(GUI* gui, bool* show_window, string name) : Panel(show_window, name){
  //---------------------------


  //---------------------------
}
GUI_dialog::~GUI_dialog(){}

//Main function
void GUI_dialog::design_panel(){
  //---------------------------

  this->capture_command();

  //---------------------------
}

//Subfunction
void GUI_dialog::capture_command(){
  ImGuiIO& io = ImGui::GetIO();
  //---------------------------

  // open Dialog Simple
if (ImGui::Button("Open File Dialog"))
  ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".cpp,.h,.hpp", ".");

// display
if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
{
  // action if OK
  if (ImGuiFileDialog::Instance()->IsOk())
  {
    std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
    std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
    // action
  }

  // close
  ImGuiFileDialog::Instance()->Close();
}


/*
  ImTextureID my_tex_id = io.Fonts->TexID;
  float my_tex_w = (float)io.Fonts->TexWidth;
  float my_tex_h = (float)io.Fonts->TexHeight;
  ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
  ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
  ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
  ImVec4 border_col = ImGui::GetStyleColorVec4(ImGuiCol_Border);
  ImGui::Image(my_tex_id, ImVec2(my_tex_w, my_tex_h), uv_min, uv_max, tint_col, border_col);
*/
  //---------------------------
}
