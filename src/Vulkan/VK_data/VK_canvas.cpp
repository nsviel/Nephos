#include "VK_canvas.h"

#include <Vulkan/Namespace.h>


//Constructor / Destructor
VK_canvas::VK_canvas(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_buffer = new VK_buffer(struct_vulkan);
  this->vk_data = new VK_data(struct_vulkan);

  //---------------------------
}
VK_canvas::~VK_canvas(){}

//Main function
void VK_canvas::init(){
  utl::type::Data* data = new utl::type::Data();
  //---------------------------

  //Generic quad coordinates and UV
  vector<vec3> xyz;
  xyz.push_back(vec3(1.0f, -1.0f, 0.0f));
  xyz.push_back(vec3(-1.0f, -1.0f, 0.0f));
  xyz.push_back(vec3(-1.0f, 1.0f, 0.0f));

  xyz.push_back(vec3(1.0f, 1.0f, 0.0f));
  xyz.push_back(vec3(1.0f, -1.0f, 0.0f));
  xyz.push_back(vec3(-1.0f, 1.0f, 0.0f));

  vector<vec2> uv;
  uv.push_back(vec2(1.0f,  0.0f));
  uv.push_back(vec2(0.0f,  0.0f));
  uv.push_back(vec2(0.0f,  1.0f));

  uv.push_back(vec2(1.0f,  1.0f));
  uv.push_back(vec2(1.0f,  0.0f));
  uv.push_back(vec2(0.0f,  1.0f));

  data->xyz = xyz;
  data->uv = uv;
  data->draw_type_name = "triangle";

  struct_vulkan->data.canvas.data = data;

  vk_buffer->create_buffers(&struct_vulkan->data.canvas);

  //---------------------------
}
void VK_canvas::clean(){
  //---------------------------

  vk_buffer->clean_buffers(&struct_vulkan->data.canvas);

  //---------------------------
}
