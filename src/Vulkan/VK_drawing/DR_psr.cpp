#include "DR_psr.h"

#include <VK_pipeline/VK_pipeline.h>
#include <VK_command/VK_submit.h>
#include <VK_main/VK_engine.h>
#include <VK_struct/struct_vulkan.h>
#include <VK_command/VK_command.h>
#include <VK_presentation/VK_canvas.h>
#include <VK_binding/VK_descriptor.h>
#include <VK_camera/VK_viewport.h>
#include <VK_camera/VK_viewport.h>
#include <ENG_shader/PSR/PSR_param.h>


//Constructor / Destructor
DR_psr::DR_psr(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->struct_vulkan = vk_engine->get_struct_vulkan();
  this->vk_command = new VK_command(vk_engine);
  this->vk_descriptor = vk_engine->get_vk_descriptor();
  this->vk_submit = new VK_submit(vk_engine);
  this->vk_viewport = vk_engine->get_vk_viewport();

  //---------------------------
}
DR_psr::~DR_psr(){}

//Main function
void DR_psr::draw_psr(Struct_renderpass* renderpass){
  timer_time t1 = timer.start_t();
  //---------------------------

  this->update_descriptor(renderpass);
  this->record_command(renderpass);
  //this->submit_command(renderpass);

  //---------------------------
  struct_vulkan->time.renderpass_psr.push_back(timer.stop_ms(t1));
}

//Subfunction
void DR_psr::update_descriptor(Struct_renderpass* renderpass){
  //---------------------------

  Frame* frame_edl = struct_vulkan->renderpass_edl.get_rendering_frame();
  Struct_pipeline* pipeline = renderpass->get_pipeline_byName("triangle");
  vk_descriptor->update_descriptor_sampler(&pipeline->binding, &frame_edl->color);
  vk_descriptor->update_descriptor_sampler(&pipeline->binding, &frame_edl->depth);

  //---------------------------
}
void DR_psr::record_command(Struct_renderpass* renderpass){
  Frame* frame = renderpass->get_rendering_frame();
  //---------------------------

  vkResetCommandBuffer(renderpass->command_buffer, 0);
  vk_command->start_command_buffer_primary(renderpass->command_buffer);
  vk_command->start_render_pass(renderpass, frame, false);
  vk_viewport->cmd_viewport(renderpass);
  this->cmd_draw(renderpass);
  vk_command->stop_render_pass(renderpass);
  vk_command->stop_command_buffer(renderpass->command_buffer);

  //---------------------------
}
void DR_psr::submit_command(Struct_renderpass* renderpass){
  //---------------------------

  Frame* frame_swap = struct_vulkan->swapchain.get_frame_inflight();
  Struct_submit_command command;
  command.command_buffer = renderpass->command_buffer;
  command.semaphore_to_wait = frame_swap->semaphore_edl_ready;
  command.semaphore_to_run = frame_swap->semaphore_psr_ready;
  command.fence = VK_NULL_HANDLE;
  command.wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  //vk_submit->submit_graphics_command(&command);

  //---------------------------
}

//Command function
void DR_psr::cmd_draw(Struct_renderpass* renderpass){
  //---------------------------
/*
  //Pipeline
  Struct_pipeline* pipeline = vk_pipeline->get_pipeline_byName(renderpass, "triangle");
  vkCmdBindPipeline(renderpass->command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline);

  edl_shader->update_shader();
  EDL_param* edl_param = edl_shader->get_edl_param();

  //Descriptor
  vk_uniform->update_uniform("PSR_param", &pipeline->binding, *edl_param);
  vkCmdBindDescriptorSets(renderpass->command_buffer, PIPELINE_GRAPHICS, pipeline->layout, 0, 1, &pipeline->binding.descriptor.set, 0, nullptr);

  Struct_data* data = vk_canvas->get_data_canvas();
  vk_cmd->cmd_draw_data(renderpass, data);
*/
  //---------------------------
}
