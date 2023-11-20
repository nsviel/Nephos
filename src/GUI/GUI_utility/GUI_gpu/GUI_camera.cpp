#include "GUI_camera.h"

#include <GUI.h>
#include <Vulkan.h>
#include <VK_main/VK_engine.h>
#include <GUI_main/GUI_render/GUI_render.h>
#include <UTL_capture/UTL_v4l2/V4L2_video.h>
#include <UTL_capture/UTL_v4l2/V4L2_camera.h>


//Constructor / Destructor
GUI_camera::GUI_camera(GUI* gui){
  //---------------------------

  GUI_render* gui_render = gui->get_gui_render();
  Vulkan* gui_vulkan = gui_render->get_gui_vulkan();
  this->vk_engine = gui_vulkan->get_vk_engine();
  this->utl_video = new V4L2_video();
  this->utl_stream = new V4L2_camera();

  //---------------------------
}
GUI_camera::~GUI_camera(){}

//Main function
void GUI_camera::draw_video(string path){
  //---------------------------

  utl_stream->load_stream(path);
  uint8_t* data = utl_stream->get_frame_data();
  if(data != nullptr){
    this->convert_data_into_texture(data);
    this->display_frame();
  }

  //---------------------------
}

//Subfunction
void GUI_camera::convert_data_into_texture(uint8_t* data){
  //---------------------------

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

  //---------------------------
}
void GUI_camera::display_frame(){
  //---------------------------

  ImVec2 panel_size = ImGui::GetContentRegionAvail();
  ImGui::Image(texture, ImVec2{panel_size.x, panel_size.y});

  //---------------------------
}
void GUI_camera::restart_video(){
  //---------------------------

  utl_stream->clean_video();

  //---------------------------
}
