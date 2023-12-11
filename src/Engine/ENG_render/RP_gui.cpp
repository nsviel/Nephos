#include "RP_gui.h"

#include <Node/Engine.h>
#include <Vulkan.h>
#include <VK_main/VK_imgui.h>
#include <VK_main/VK_engine.h>
#include <VK_drawing/VK_drawing.h>


//Constructor / Destructor
RP_gui::RP_gui(Engine* engine){
  //---------------------------

  Vulkan* eng_vulkan = engine->get_eng_vulkan();

  this->vk_engine = eng_vulkan->get_vk_engine();
  this->vk_imgui = eng_vulkan->get_vk_imgui();

  //---------------------------
}
RP_gui::~RP_gui(){}

//Init function
void RP_gui::init_renderpass(){
  //---------------------------

  //Renderpass
  vk::structure::Renderpass* renderpass = new vk::structure::Renderpass();
  renderpass->name = "gui";
  renderpass->target = "presentation";

  //Pipeline
  this->create_subpass(renderpass);

  //---------------------------
  vk_engine->add_renderpass_description(renderpass);
}
void RP_gui::create_subpass(vk::structure::Renderpass* renderpass){
  //---------------------------

  Shader_info* shader_info = new Shader_info();
  shader_info->title = "Canvas";
  shader_info->folder = "Canvas";
  shader_info->path_spir_vs = "../src/GUI/GUI_main/Render/Shader/spir/shader_empty_vs.spv";
  shader_info->path_spir_fs = "../src/GUI/GUI_main/Render/Shader/spir/shader_empty_fs.spv";
  shader_info->compile_shader = false;
  shader_info->with_depth_test = false;

  vk::structure::Subpass* subpass = new vk::structure::Subpass();
  subpass->target = "presentation";
  subpass->draw_task = [this](vk::structure::Subpass* subpass){RP_gui::draw(subpass);};

  vk::structure::Pipeline* pipeline = new vk::structure::Pipeline();
  pipeline->definition.name = "triangle";
  pipeline->definition.purpose = "presentation";
  pipeline->definition.topology = "triangle";
  pipeline->definition.shader = shader_info;
  subpass->vec_pipeline.push_back(pipeline);

  //---------------------------
  renderpass->vec_subpass.push_back(subpass);
}

void RP_gui::draw(vk::structure::Subpass* subpass){
  //---------------------------

  vk_imgui->draw(subpass->command_buffer);

  //---------------------------
}
