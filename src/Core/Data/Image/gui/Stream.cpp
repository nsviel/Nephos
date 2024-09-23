#include "Stream.h"

#include <Data/Image/Namespace.h>
#include <Vulkan/Namespace.h>


namespace dat::img::gui{

//Constructor / Destructor
Stream::Stream(dat::img::Node* node_image){
  //---------------------------

  vk::Node* node_vulkan = node_image->get_node_vulkan();

  this->vk_interface = node_vulkan->get_vk_interface();

  //---------------------------
}
Stream::~Stream(){}

//Main function
void Stream::draw_stream(std::shared_ptr<utl::media::Image> utl_image, ImVec2 dimension){
  if(!check_image(utl_image)) return;
  //---------------------------

  this->convert_data_into_texture(utl_image);
  this->render_image(utl_image, dimension);

  //---------------------------
}

//Subfunction
bool Stream::check_image(std::shared_ptr<utl::media::Image> utl_image){
  //---------------------------

  if(utl_image == nullptr) return false;
  if(utl_image->size == 0) return false;
  if(utl_image->format == "") return false;

  //---------------------------
  return true;
}
void Stream::convert_data_into_texture(std::shared_ptr<utl::media::Image> utl_image){
  //---------------------------

  bool update = (current_timestamp != utl_image->timestamp);

  //Load texture into vulkan
  if(update){
    //vk_interface->insert_texture(utl_image);
    current_timestamp = utl_image->timestamp;
  }

  //---------------------------
}
void Stream::render_image(std::shared_ptr<utl::media::Image> utl_image, ImVec2& dimension){
  if(utl_image->texture_ID == -1) return;
  //---------------------------

  //ImGui::Image(utl_image->gui_texture_ID, dimension);

  //---------------------------
}


}
