#include "Renderer.h"

#include <Vulkan/Namespace.h>


namespace vk::draw{

//Constructor / Destructor
Renderer::Renderer(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_command = new vk::command::Command(struct_vulkan);
  this->vk_submit = new vk::command::Submit(struct_vulkan);
  this->vk_profiler = new vk::instance::Profiler(struct_vulkan);

  //---------------------------
}
Renderer::~Renderer(){}

//Main function
void Renderer::run_renderpass(vk::structure::Renderpass* renderpass){
  vk_profiler->start();
  //---------------------------

  this->start_renderpass(renderpass);
  this->draw_subpass(renderpass);
  vk_command->stop_render_pass(renderpass);

  //---------------------------
}
void Renderer::submit_command(vk::structure::Renderpass* renderpass){
  vk::structure::Command& command = renderpass->command;
  //---------------------------

  command.vec_wait_stage.push_back(VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT);
  vk_submit->submit_command_render(&command);

  //---------------------------
  string name = "rp_" + renderpass->name;
  vk_profiler->stop(name);
}

//Subfunction
void Renderer::start_renderpass(vk::structure::Renderpass* renderpass){
  //---------------------------

  VkFramebuffer fbo;
  if(renderpass->target == "graphics" || renderpass->target == "transfert"){
    fbo = renderpass->framebuffer->fbo;
  }
  else if(renderpass->target == "presentation"){
    fbo = struct_vulkan->swapchain.get_frame_presentation()->fbo;
  }
  else{
    cout<<"[error] Renderpass target not recognized ["<<renderpass->target<<"]"<<endl;
  }
  vk_command->start_render_pass(renderpass, fbo, false);

  //---------------------------
}
void Renderer::draw_subpass(vk::structure::Renderpass* renderpass){
  vk::structure::Command command;
  //---------------------------

  for(int j=0; j<renderpass->vec_subpass.size(); j++){
    vk::structure::Subpass* subpass = renderpass->vec_subpass[j];
    subpass->command_buffer = renderpass->command_buffer;
    subpass->draw_task(subpass);
  }

  command.vec_command_buffer.push_back(renderpass->command_buffer);

  //---------------------------
  renderpass->command = command;
}
void Renderer::wait_end_rendering(VkFence& fence){
  //---------------------------

  vkWaitForFences(struct_vulkan->device.device, 1, &fence, VK_TRUE, UINT64_MAX);
  vkResetFences(struct_vulkan->device.device, 1, &fence);

  //---------------------------
}

}
