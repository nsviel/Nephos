#include "Renderpass.h"

#include <Engine/Node.h>
#include <Vulkan/Namespace.h>
#include <Engine/Render/Namespace.h>


namespace rnd::gui{

//Constructor / Destructor
Renderpass::Renderpass(eng::render::Manager* node_render){
  //---------------------------

  vk::Node* node_vulkan = node_render->get_node_vulkan();

  this->vk_engine = node_vulkan->get_vk_engine();
  this->vk_imgui = node_vulkan->get_vk_imgui();

  //---------------------------
}
Renderpass::~Renderpass(){}

//Init function
void Renderpass::init_renderpass(){
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
void Renderpass::create_subpass(vk::structure::Renderpass* renderpass){
  //---------------------------

  utl::shader::Info* shader_info = new utl::shader::Info();
  shader_info->title = "Canvas";
  shader_info->folder = "Canvas";
  shader_info->path_spir_vs = "../shader/Empty/spir/shader_empty_vs.spv";
  shader_info->path_spir_fs = "../shader/Empty/spir/shader_empty_fs.spv";
  shader_info->compile_shader = false;
  shader_info->with_depth_test = false;

  vk::structure::Subpass* subpass = new vk::structure::Subpass();
  subpass->target = "presentation";
  subpass->draw_task = [this](vk::structure::Subpass* subpass){Renderpass::draw(subpass);};

  vk::structure::Pipeline* pipeline = new vk::structure::Pipeline();
  pipeline->definition.name = "triangle";
  pipeline->definition.purpose = "presentation";
  pipeline->definition.topology = "triangle";
  pipeline->definition.shader = shader_info;
  subpass->vec_pipeline.push_back(pipeline);

  //---------------------------
  renderpass->vec_subpass.push_back(subpass);
}

void Renderpass::draw(vk::structure::Subpass* subpass){
  //---------------------------

  vk_imgui->draw(subpass->command_buffer);

  //---------------------------
}

}
