#include "Stream.h"

#include <Data/Image/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace dat::img::gui{

//Constructor / Destructor
Stream::Stream(dat::img::Node* node_image){
  //---------------------------

  vk::Node* node_vulkan = node_image->get_node_vulkan();

  this->vk_data = node_vulkan->get_vk_data();
  this->vk_render = node_vulkan->get_vk_render();

  //---------------------------
}
Stream::~Stream(){}

//Main function
void Stream::draw_stream(std::shared_ptr<utl::base::Image> image, ImVec2 dimension){
  if(!check_image(image)) return;
  //---------------------------

  this->update_texture(image);
  this->render_image(image, dimension);

  //---------------------------
}

//Subfunction
bool Stream::check_image(std::shared_ptr<utl::base::Image> image){
  //---------------------------

  if(!image) return false;
  if(image->size == 0) return false;
  if(image->format == "") return false;

  //---------------------------
  return true;
}
void Stream::update_texture(std::shared_ptr<utl::base::Image> image){
  //---------------------------

  bool update = (current_timestamp != image->timestamp);
  if(update){
    vk_data->update_image(image);
    current_timestamp = image->timestamp;
  }

  //---------------------------
}
void Stream::render_image(std::shared_ptr<utl::base::Image> image, ImVec2& dimension){
  //---------------------------

  glm::vec2 dim = glm::vec2(dimension.x, dimension.y);
  vk_render->draw_image(image, dim);

  //---------------------------
}


}
