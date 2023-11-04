#include "VK_canvas.h"

#include <VK_main/VK_engine.h>
#include "../VK_struct/struct_vulkan.h"
#include "../VK_data/VK_buffer.h"
#include "../VK_data/VK_data.h"
#include "../VK_image/VK_texture.h"
#include "../VK_binding/VK_binding.h"


//Constructor / Destructor
VK_canvas::VK_canvas(VK_engine* vk_engine){
  //---------------------------

  this->struct_vulkan = vk_engine->get_struct_vulkan();
  this->vk_buffer = new VK_buffer(vk_engine);
  this->vk_data = vk_engine->get_vk_data();
  this->vk_texture = vk_engine->get_vk_texture();
  this->vk_binding = new VK_binding(vk_engine);

  //---------------------------
}
VK_canvas::~VK_canvas(){}

//Main function
void VK_canvas::create_canvas(){
  Object* canvas_obj = new Object();
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

  this->canvas = new Struct_data();
  this->canvas->object = canvas_obj;

  vk_data->check_for_attribut(canvas);
  vk_buffer->create_buffer(canvas);

  //---------------------------
}
void VK_canvas::clean_canvas(){
  //---------------------------

  vk_buffer->clean_buffer(canvas);
  vk_texture->clean_texture(canvas);

  //---------------------------
}
