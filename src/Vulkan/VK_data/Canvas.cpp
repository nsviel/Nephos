#include "Canvas.h"

#include <Vulkan/Namespace.h>


namespace vk::data{

//Constructor / Destructor
Canvas::Canvas(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_buffer = new Buffer(struct_vulkan);
  this->vk_data = new vk::data::Data(struct_vulkan);

  //---------------------------
}
Canvas::~Canvas(){}

//Main function
void Canvas::init(){
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
void Canvas::clean(){
  //---------------------------

  vk_buffer->clean_buffers(&struct_vulkan->data.canvas);

  //---------------------------
}

}
