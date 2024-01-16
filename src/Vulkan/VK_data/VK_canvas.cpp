#include "VK_canvas.h"

#include <Vulkan/VK_struct/Namespace.h>
#include <Vulkan/VK_data/VK_buffer.h>
#include <Vulkan/VK_data/VK_data.h>


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
  entity::Object* canvas_obj = new entity::Object();
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

  canvas_obj->name = "canvas";
  canvas_obj->xyz = xyz;
  canvas_obj->uv = uv;
  canvas_obj->draw_type_name = "triangle";

  struct_vulkan->data.canvas.object = canvas_obj;

  vk_buffer->create_buffers(&struct_vulkan->data.canvas);

  //---------------------------
}
void VK_canvas::clean(){
  //---------------------------

  vk_buffer->clean_buffers(&struct_vulkan->data.canvas);

  //---------------------------
}
