#include "Stream.h"

#include <Engine/Node.h>
#include <Vulkan/Node.h>
#include <Vulkan/VK_main/Texture.h>
#include <Vulkan/VK_struct/Namespace.h>
#include <GUI/Namespace.h>


namespace eng::render::gui{

//Constructor / Destructor
Stream::Stream(eng::Node* engine){
  //---------------------------

  vk::Node* vulkan = engine->get_eng_vulkan();
  this->vk_texture = vulkan->get_vk_texture();
  this->vk_imgui = vulkan->get_vk_imgui();
  this->imgui_texture = 0;

  //---------------------------
}
Stream::~Stream(){}

//Main function
void Stream::draw_stream(utl::media::Image* utl_image, ImVec2 size){
  if(utl_image->size == 0) return;
  //---------------------------

  this->convert_data_into_texture(utl_image, size);
  this->render_image(size);

  //---------------------------
}

//Subfunction
void Stream::convert_data_into_texture(utl::media::Image* utl_image, ImVec2& size){
  //---------------------------

  if(imgui_texture == 0){
    //Load texture into vulkan
    this->vk_texture_UID = vk_texture->load_texture(utl_image);
    this->imgui_texture = vk_imgui->create_imgui_texture(vk_texture_UID);
  }else if(utl_image->new_data){
    //update texture data
    vk_texture->update_texture(vk_texture_UID);
    utl_image->new_data = false;
  }

  //---------------------------
}
void Stream::render_image(ImVec2& size){
  if(imgui_texture == 0) return;
  //---------------------------

  ImGui::Image(imgui_texture, size);

  //---------------------------
}


}
