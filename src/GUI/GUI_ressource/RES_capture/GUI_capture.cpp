#include "GUI_capture.h"

#include <RES_gpu/GUI_video.h>
#include <RES_gpu/GUI_image.h>
#include <TAB_render/TAB_render.h>
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

  gui_video->draw_video("../media/vulkano.mp4");
  gui_image->draw_image_static("../media/vulkano.jpg");

  //---------------------------
}
