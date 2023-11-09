#include "GUI_image.h"

#include <GUI.h>
#include <VK_main/VK_engine.h>
#include <VK_main/VK_render.h>
#include <GUI_main/GUI_render/GUI_render.h>


//Constructor / Destructor
GUI_image::GUI_image(GUI* gui){
  //---------------------------

  GUI_render* gui_render = gui->get_gui_render();
  VK_engine* vk_engine = gui_render->get_vk_engine();
  this->vk_render = vk_engine->get_vk_render();

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
  static Struct_image* image;
  //---------------------------

  if(image == nullptr){
    image = vk_render->load_texture_from_file(path);
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
