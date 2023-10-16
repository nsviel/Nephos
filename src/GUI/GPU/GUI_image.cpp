#include "GUI_image.h"

#include <Engine.h>


//Constructor / Destructor
GUI_image::GUI_image(Engine* engine){
  //---------------------------

  this->gpu_texture = engine->get_gpu_texture();
  this->image_current = nullptr;

  //---------------------------
}
GUI_image::~GUI_image(){}

//Main function
void GUI_image::display_image(string path){
  //---------------------------

  static bool once = true;
  if(once){
    Struct_image* image = gpu_texture->load_texture(path);
    this->descriptor  = ImGui_ImplVulkan_AddTexture(image->sampler, image->view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
  }
  once = false;

  ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
  ImGui::Image(descriptor, ImVec2{viewportPanelSize.x, viewportPanelSize.y});

  //---------------------------
}

//Subfunction
