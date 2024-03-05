#include "Stream.h"

#include <Engine/Node.h>
#include <Vulkan/Namespace.h>
#include <GUI/Namespace.h>


namespace eng::render::gui{

//Constructor / Destructor
Stream::Stream(eng::Node* engine){
  //---------------------------

  vk::Node* vulkan = engine->get_node_vulkan();
  this->vk_texture = vulkan->get_vk_texture();
  this->vk_imgui = vulkan->get_vk_imgui();

  //---------------------------
}
Stream::~Stream(){}

//Main function
void Stream::draw_stream(utl::media::Image* utl_image, ImVec2 size){
  if(utl_image->size == 0) return;
  //---------------------------

  this->convert_data_into_texture(utl_image);
  this->render_image(utl_image, size);

  //---------------------------
}

//Subfunction
void Stream::convert_data_into_texture(utl::media::Image* utl_image){
  if(utl_image->format == "") return;
  //---------------------------

  //Load texture into vulkan
  if(utl_image->texture_ID == -1){
    vk_imgui->load_texture(utl_image);
  //update texture data
  }else if(utl_image->new_data){
    vk_texture->update_texture(utl_image);
    utl_image->new_data = false;
  }

  //---------------------------
}
void Stream::render_image(utl::media::Image* utl_image, ImVec2& size){
  if(utl_image->texture_ID == -1) return;
  //---------------------------

  ImGui::Image(utl_image->gui_ID, size);

  //---------------------------
}


}
