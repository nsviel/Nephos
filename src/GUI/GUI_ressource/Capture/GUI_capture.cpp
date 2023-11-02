#include "GUI_capture.h"

#include <GPU/GUI_video.h>
#include <GPU/GUI_image.h>
#include <TAB_render/GUI_tab_render.h>
#include <GUI.h>


//Constructor / Destructor
GUI_capture::GUI_capture(GUI* gui, bool* show_window, string name) : BASE_panel(show_window, name){
  //---------------------------

  this->gui_image = new GUI_image(gui);
  this->gui_video = new GUI_video(gui);
  this->gui = gui;

  //---------------------------
}
GUI_capture::~GUI_capture(){}

//Main function
void GUI_capture::design_panel(){
  //---------------------------

  this->capture_command();

  //---------------------------
}

//Subfunction
void GUI_capture::capture_command(){
  ImGuiIO& io = ImGui::GetIO();
  //---------------------------

//sayHello();
  gui_video->draw_video("/home/aether/Desktop/Nephos/media/vulkano.mp4");
  gui_image->draw_image("/home/aether/Desktop/Nephos/media/vulkano.jpg");

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
