#include "GUI_renderpass.h"

#include <Vulkan.h>
#include <VK_main/VK_imgui.h>
#include <VK_main/VK_engine.h>


namespace gui{

//Constructor / Destructor
GUI_renderpass::GUI_renderpass(Vulkan* vulkan){
  //---------------------------

  this->vk_imgui = vulkan->get_vk_imgui();
  this->vk_engine = vulkan->get_vk_engine();

  //---------------------------
}
GUI_renderpass::~GUI_renderpass(){}

//Init function
void GUI_renderpass::init_renderpass(){
  //---------------------------

  //Renderpass
  Struct_vk_renderpass* renderpass = new Struct_vk_renderpass();
  renderpass->name = "gui";
  renderpass->target = "presentation";

  //Pipeline
  this->create_subpass(renderpass);

  //---------------------------
  vk_engine->add_renderpass_description(renderpass);
}
void GUI_renderpass::create_subpass(Struct_vk_renderpass* renderpass){
  //---------------------------

  Shader_info* shader_info = new Shader_info();
  shader_info->title = "Canvas";
  shader_info->folder = "Canvas";
  shader_info->path_spir_vs = "../src/GUI/GUI_main/GUI_render/Shader/spir/shader_empty_vs.spv";
  shader_info->path_spir_fs = "../src/GUI/GUI_main/GUI_render/Shader/spir/shader_empty_fs.spv";
  shader_info->compile_shader = false;
  shader_info->with_depth_test = false;

  Struct_vk_subpass* subpass = new Struct_vk_subpass();
  subpass->target = "presentation";
  subpass->draw_task = [this](Struct_vk_subpass* subpass){GUI_renderpass::draw(subpass);};

  Struct_vk_pipeline* pipeline = new Struct_vk_pipeline();
  pipeline->definition.name = "triangle";
  pipeline->definition.purpose = "presentation";
  pipeline->definition.topology = "triangle";
  pipeline->definition.shader = shader_info;
  subpass->vec_pipeline.push_back(pipeline);

  //---------------------------
  renderpass->vec_subpass.push_back(subpass);
}

//Draw function
void GUI_renderpass::draw(Struct_vk_subpass* subpass){
  //---------------------------

  vk_imgui->draw(subpass->command_buffer);

  //---------------------------
}

}
