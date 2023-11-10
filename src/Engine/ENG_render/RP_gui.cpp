#include "RP_gui.h"

#include <Engine.h>
#include <Vulkan.h>
#include <VK_main/VK_imgui.h>
#include <VK_main/VK_engine.h>
#include <VK_main/VK_render.h>
#include <VK_drawing/VK_drawing.h>


//Constructor / Destructor
RP_gui::RP_gui(Engine* engine){
  //---------------------------

  Vulkan* eng_vulkan = engine->get_eng_vulkan();

  this->vk_engine = eng_vulkan->get_vk_engine();
  this->vk_render = eng_vulkan->get_vk_render();

  //---------------------------
}
RP_gui::~RP_gui(){}

//Init function
void RP_gui::init_renderpass(){
  //---------------------------

  //Renderpass
  Struct_renderpass* renderpass = new Struct_renderpass();
  renderpass->name = "gui";
  renderpass->target = "presentation";

  //Pipeline
  this->create_subpass(renderpass);

  //---------------------------
  vk_render->add_renderpass_description(renderpass);
}
void RP_gui::create_subpass(Struct_renderpass* renderpass){
  //---------------------------

  Shader_info* shader_info = new Shader_info();
  shader_info->title = "Canvas";
  shader_info->folder = "Canvas";
  shader_info->path_spir_vs = "../src/GUI/GUI_main/GUI_render/Shader/spir/shader_empty_vs.spv";
  shader_info->path_spir_fs = "../src/GUI/GUI_main/GUI_render/Shader/spir/shader_empty_fs.spv";
  shader_info->compile_shader = false;
  shader_info->with_depth_test = false;

  Struct_subpass* subpass = new Struct_subpass();
  subpass->target = "presentation";
  subpass->draw_task = [this](Struct_subpass* subpass){RP_gui::draw(subpass);};

  Struct_pipeline* pipeline = new Struct_pipeline();
  pipeline->definition.name = "triangle";
  pipeline->definition.purpose = "presentation";
  pipeline->definition.topology = "triangle";
  pipeline->definition.shader = shader_info;
  subpass->vec_pipeline.push_back(pipeline);

  //---------------------------
  renderpass->vec_subpass.push_back(subpass);
}

void RP_gui::draw(Struct_subpass* subpass){
  VK_drawing vk_drawing(vk_engine);
  //---------------------------


  //---------------------------
}
