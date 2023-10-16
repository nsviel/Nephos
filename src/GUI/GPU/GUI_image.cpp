#include "GUI_image.h"

#include <Engine.h>
#include <GPU/GPU_texture.h>


//Constructor / Destructor
GUI_image::GUI_image(Engine* engine){
  //---------------------------

  this->gpu_texture = engine->get_gpu_texture();

  //---------------------------
}
GUI_image::~GUI_image(){}

//Main function
void GUI_image::display_image(string path){
  //---------------------------

  Struct_image* image = gpu_texture->load_texture(path);
  VkDescriptorSet descriptor = ImGui_ImplVulkan_AddTexture(image->sampler, image->view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

  ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
  ImGui::Image(descriptor, ImVec2{viewportPanelSize.x, viewportPanelSize.y});

  //vk_texture->clean_texture(Struct_image* texture);


  //---------------------------
}
