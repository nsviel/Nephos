#include "DR_edl.h"

#include <Engine.h>
#include <Vulkan/VK_command/VK_cmd.h>
#include <Vulkan/VK_pipeline/VK_pipeline.h>
#include <Vulkan/VK_command/VK_submit.h>
#include <Vulkan/VK_engine.h>
#include <Vulkan/VK_struct.h>
#include <Vulkan/VK_command/VK_command.h>
#include <Vulkan/VK_presentation/VK_canvas.h>
#include <Vulkan/VK_binding/VK_descriptor.h>
#include <Vulkan/VK_binding/VK_uniform.h>
#include <ENG_shader/Shader.h>
#include <ENG_shader/EDL/EDL_shader.h>


//Constructor / Destructor
DR_edl::DR_edl(VK_engine* vk_engine){
  //---------------------------

  Engine* engine = vk_engine->get_engine();
  Shader* shaderManager = engine->get_shaderManager();
  this->edl_shader = shaderManager->get_edl_shader();

  this->vk_engine = vk_engine;
  this->vk_struct = vk_engine->get_vk_struct();
  this->vk_command = vk_engine->get_vk_command();
  this->vk_cmd = vk_engine->get_vk_cmd();
  this->vk_descriptor = vk_engine->get_vk_descriptor();
  this->vk_submit = vk_engine->get_vk_submit();
  this->vk_uniform = vk_engine->get_vk_uniform();
  this->vk_canvas = vk_engine->get_vk_canvas();

  //---------------------------
}
DR_edl::~DR_edl(){}

//Main function
void DR_edl::draw_edl(Struct_renderpass* renderpass){
  timer_time t1 = timer.start_t();
  //---------------------------

  this->update_descriptor(renderpass);
  this->record_command(renderpass);
  this->submit_command(renderpass);

  //---------------------------
  vk_struct->time.renderpass_edl.push_back(timer.stop_ms(t1));
}

//Subfunction
void DR_edl::update_descriptor(Struct_renderpass* renderpass){
  //---------------------------

  Frame* frame_scene = vk_struct->renderpass_scene.get_rendering_frame();
  Struct_pipeline* pipeline = renderpass->get_pipeline_byName("triangle_EDL");
  vk_descriptor->update_descriptor_sampler(&pipeline->binding, &frame_scene->color);
  vk_descriptor->update_descriptor_sampler(&pipeline->binding, &frame_scene->depth);

  //---------------------------
}
void DR_edl::record_command(Struct_renderpass* renderpass){
  Frame* frame = renderpass->get_rendering_frame();
  //---------------------------


  vk_command->start_render_pass(renderpass, frame, false);
  vk_cmd->cmd_viewport(renderpass);
  this->cmd_draw(renderpass);
  vk_command->stop_render_pass(renderpass);

  //---------------------------
}
void DR_edl::submit_command(Struct_renderpass* renderpass){
  //---------------------------

  Frame* frame_swap = vk_struct->swapchain.get_frame_inflight();
  renderpass->semaphore_to_wait = frame_swap->semaphore_scene_ready;
  renderpass->semaphore_to_run = frame_swap->semaphore_edl_ready;
  renderpass->fence = VK_NULL_HANDLE;
  vk_submit->submit_graphics_command(renderpass);

  //---------------------------
}

//Command function
void DR_edl::cmd_draw(Struct_renderpass* renderpass){
  //---------------------------

  Struct_pipeline* pipeline = renderpass->get_pipeline_byName("triangle_EDL");
  EDL_param* edl_param = edl_shader->get_edl_param();
  Struct_data* canvas = vk_canvas->get_data_canvas();

  vk_cmd->cmd_bind_pipeline(renderpass, "triangle_EDL");
  edl_shader->update_shader();
  vk_uniform->update_uniform_edl("EDL_param", &pipeline->binding, *edl_param);
  vk_cmd->cmd_bind_descriptor(renderpass, "triangle_EDL", pipeline->binding.descriptor.set);
  vk_cmd->cmd_draw_data(renderpass, canvas);

  //---------------------------
}
