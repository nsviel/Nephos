#include "VK_render.h"

#include <VK_main/VK_engine.h>
#include <VK_drawing/VK_drawing.h>
#include <VK_main/Struct_vulkan.h>
#include <ELE_specific/FPS_counter.h>

//Constructor / Destructor
VK_render::VK_render(Struct_vulkan* struct_vulkan){
  //---------------------------

  this->vk_drawing = new VK_drawing(struct_vulkan);
  this->vk_texture = new VK_texture(struct_vulkan);
  this->struct_vulkan = struct_vulkan;
  this->fps_counter = new FPS_counter(60);

  //---------------------------
}
VK_render::~VK_render(){}

//Main function
void VK_render::loop(){
  //---------------------------

  vk_drawing->draw_frame();

  //---------------------------
  fps_counter->update();
  struct_vulkan->info.engine_fps = fps_counter->get_fps();
}
void VK_render::add_renderpass_description(Struct_renderpass* renderpass){
  //---------------------------

  struct_vulkan->render.vec_renderpass.push_back(renderpass);

  //---------------------------
}

//Texture function
Struct_image* VK_render::load_texture_from_file(string path){
  //---------------------------

  Struct_image* texture = vk_texture->load_texture_from_file(path);

  //---------------------------
  return texture;
}
Struct_image* VK_render::load_texture_from_frame(AVFrame* frame){
  //---------------------------

  Struct_image* texture = vk_texture->load_texture_from_frame(frame);

  //---------------------------
  return texture;
}
