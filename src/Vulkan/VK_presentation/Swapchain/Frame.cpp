#include "Frame.h"

#include <Vulkan/Namespace.h>


namespace vk::presentation{

//Constructor / Destructor
Frame::Frame(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_image = new vk::image::Image(vk_struct);
  this->vk_color = new vk::image::Color(vk_struct);

  //---------------------------
}
Frame::~Frame(){}

//Main function
void Frame::create_frame(){
  //---------------------------

  if(vk_struct->swapchain.vec_image.size() == 0){
    std::cout<<"[error] swapchain image size equal zero"<<std::endl;
    return;
  }

  for(int i=0; i<vk_struct->swapchain.vec_image.size(); i++){
    vk::structure::Frame* frame = new vk::structure::Frame();
    frame->color.handle = vk_struct->swapchain.vec_image[i];
    frame->color.format = vk_color->find_color_format();
    frame->color.aspect = VK_IMAGE_ASPECT_COLOR_BIT;
    frame->color.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    vk_image->create_image_view(&frame->color);

    vk_struct->swapchain.vec_frame.push_back(frame);
  }

  //---------------------------
}
void Frame::clean_frame(){
  std::vector<vk::structure::Frame*>& vec_frame = vk_struct->swapchain.vec_frame;
  //---------------------------

  //Vec images
  for(int i=0; i<vec_frame.size(); i++){
    vk::structure::Frame* frame = vec_frame[i];
    vk_image->clean_image_view(&frame->color);
    delete frame;
  }
  vec_frame.clear();

  //---------------------------
}

}
