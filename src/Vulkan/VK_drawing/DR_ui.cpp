#include "DR_ui.h"

#include <VK_command/VK_submit.h>
#include <VK_engine.h>
#include <VK_struct/struct_vulkan.h>
#include <VK_command/VK_command.h>
#include <VK_presentation/VK_canvas.h>
#include <VK_binding/VK_descriptor.h>
#include <VK_binding/VK_uniform.h>
#include <VK_data/VK_data.h>


//Constructor / Destructor
DR_ui::DR_ui(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->struct_vulkan = vk_engine->get_struct_vulkan();
  this->vk_command = vk_engine->get_vk_command();
  this->vk_descriptor = vk_engine->get_vk_descriptor();
  this->vk_submit = vk_engine->get_vk_submit();
  this->vk_uniform = vk_engine->get_vk_uniform();
  this->vk_data = vk_engine->get_vk_data();
  this->vk_canvas = vk_engine->get_vk_canvas();

  //---------------------------
}
DR_ui::~DR_ui(){}

//Main function
void DR_ui::draw_ui(Struct_renderpass* renderpass){
  timer_time t1 = timer.start_t();
  //---------------------------

  this->record_command(renderpass);
  this->submit_command(renderpass);

  //---------------------------
  struct_vulkan->time.renderpass_ui.push_back(timer.stop_ms(t1));
}

//Subfunction
void DR_ui::record_command(Struct_renderpass* renderpass){
  Frame* frame = struct_vulkan->swapchain.get_frame_current();
  //---------------------------

  vk_command->start_render_pass(renderpass, frame, false);
  ImGui_ImplVulkan_RenderDrawData(draw_data, renderpass->command_buffer);
  vk_command->stop_render_pass(renderpass);

  //---------------------------
}
void DR_ui::submit_command(Struct_renderpass* renderpass){
  //---------------------------

  Frame* frame_swap = struct_vulkan->swapchain.get_frame_inflight();
  renderpass->semaphore_to_wait = frame_swap->semaphore_edl_ready;
  renderpass->semaphore_to_run = frame_swap->semaphore_ui_ready;
  renderpass->fence = frame_swap->fence;
  vk_submit->submit_graphics_command(renderpass);

  //---------------------------
}
