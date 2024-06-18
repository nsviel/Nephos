#include "Stream.h"

#include <Engine/Namespace.h>
#include <Vulkan/Namespace.h>


namespace rnd{

//Constructor / Destructor
Stream::Stream(eng::Node* node_engine){
  //---------------------------

  vk::Node* node_vulkan = node_engine->get_node_vulkan();
  this->vk_texture = node_vulkan->get_vk_texture();
  this->vk_imgui = node_vulkan->get_vk_imgui();

  //---------------------------
}
Stream::~Stream(){}

//Main function
void Stream::draw_stream(utl::media::Image* utl_image, ImVec2 size){
  if(!check_image(utl_image)) return;
  //---------------------------

  this->convert_data_into_texture(utl_image);
  this->render_image(utl_image, size);

  //---------------------------
}

//Subfunction
bool Stream::check_image(utl::media::Image* utl_image){
  //---------------------------

  if(utl_image->size == 0){
    return false;
  }
  if(utl_image->format == ""){
    cout<<"[error] stream image should have format specified"<<endl;
    return false;
  }

  //---------------------------
  return true;
}
void Stream::convert_data_into_texture(utl::media::Image* utl_image){
  //---------------------------

  bool load = (utl_image->texture_ID == -1 || current_UID != utl_image->UID);
  bool update = (current_timestamp != utl_image->timestamp);

  say("----");
  say(load);
  say(current_UID);
  say(utl_image->UID);

  //Load texture into vulkan
  if(load){
    vk_texture->import_texture(utl_image);
    vk_imgui->load_texture(utl_image);
    current_UID = utl_image->UID;
  //update texture data
  }else if(update){
    vk_texture->import_texture(utl_image);
    current_timestamp = utl_image->timestamp;
  }

  //---------------------------
}
void Stream::render_image(utl::media::Image* utl_image, ImVec2& size){
  if(utl_image->texture_ID == -1) return;
  //---------------------------

  ImGui::Image(utl_image->gui_texture_ID, size);

  //---------------------------
}


}
