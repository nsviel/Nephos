#include "GUI_video.h"

#include <GUI.h>
#include <Vulkan.h>
#include <VK_main/VK_engine.h>
#include <GUI_main/GUI_render/GUI_render.h>
#include <UTL_capture/UTL_video.h>
#include <UTL_capture/UTL_stream.h>


//Constructor / Destructor
GUI_video::GUI_video(GUI* gui){
  //---------------------------

  GUI_render* gui_render = gui->get_gui_render();
  Vulkan* gui_vulkan = gui_render->get_gui_vulkan();
  this->vk_engine = gui_vulkan->get_vk_engine();
  this->utl_video = new UTL_video();
  this->utl_stream = new UTL_stream();

  //---------------------------
}
GUI_video::~GUI_video(){}

//Main function
void GUI_video::draw_video(string path){
  //---------------------------

  utl_stream->load_stream(path);
  uint8_t* data = utl_stream->acquire_next_frame();
  this->convert_data_into_texture(data);
  this->display_frame();

  //---------------------------
}

//Subfunction
void GUI_video::convert_data_into_texture(uint8_t* data){
  //---------------------------

  if(data != nullptr){
    static Struct_image* image = nullptr;

    if(image == nullptr){
      int width = utl_stream->get_frame_width();
      int height = utl_stream->get_frame_height();
      image = vk_engine->load_texture_from_data(data, width, height);
      VkDescriptorSet descriptor  = ImGui_ImplVulkan_AddTexture(image->sampler, image->view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
      this->texture = reinterpret_cast<ImTextureID>(descriptor);
    }else{
      vk_engine->update_texture_from_data(image, data);
    }
  }

  //---------------------------
}
void GUI_video::display_frame(){
  //---------------------------

  ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
  ImGui::Image(texture, ImVec2{200,200});

  //---------------------------
}
