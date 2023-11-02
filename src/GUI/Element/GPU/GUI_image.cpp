#include "GUI_image.h"

#include <GUI.h>
#include <Engine.h>


//Constructor / Destructor
GUI_image::GUI_image(GUI* gui){
  //---------------------------

  Engine* engine = gui->get_engine();
  this->gpu_texture = engine->get_gpu_texture();

  this->image = nullptr;

  //---------------------------
}
GUI_image::~GUI_image(){}

//Main function
void GUI_image::draw_image(string path){
  //---------------------------

  this->load_image(path);
  this->display_image();

  //---------------------------
}

//Subfunction
void GUI_image::load_image(string path){
  //---------------------------

  if(image == nullptr){
    this->image = gpu_texture->load_texture_from_file(path);
    this->descriptor  = ImGui_ImplVulkan_AddTexture(image->sampler, image->view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
  }

  //---------------------------
}
void GUI_image::display_image(){
  //---------------------------

  ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
  ImGui::Image(descriptor, ImVec2{viewportPanelSize.x, viewportPanelSize.y});

  //---------------------------
}
