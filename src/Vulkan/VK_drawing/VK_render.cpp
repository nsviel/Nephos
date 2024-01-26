#include "VK_render.h"

#include <Vulkan/Namespace.h>


namespace vk::draw{

//Constructor / Destructor
VK_render::VK_render(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_command = new vk::command::Command(struct_vulkan);
  this->vk_submit = new vk::command::Submit(struct_vulkan);
  this->vk_profiler = new VK_profiler(struct_vulkan);

  //---------------------------
}
VK_render::~VK_render(){}

//Main function
void VK_render::run_renderpass(vk::structure::Renderpass* renderpass){
  vk_profiler->start();
  //---------------------------

  this->start_renderpass(renderpass);
  this->draw_subpass(renderpass);
  vk_command->stop_render_pass(renderpass);

  //---------------------------
}
void VK_render::submit_command(vk::structure::Renderpass* renderpass){
  vk::structure::Command& command = renderpass->command;
  //---------------------------

  command.vec_wait_stage.push_back(VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT);
  vk_submit->submit_command_render(&command);

  //---------------------------
  string name = "rp_" + renderpass->name;
  vk_profiler->stop(name);
}

//Subfunction
void VK_render::start_renderpass(vk::structure::Renderpass* renderpass){
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
void VK_render::draw_subpass(vk::structure::Renderpass* renderpass){
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
void VK_render::wait_end_rendering(VkFence& fence){
  //---------------------------

  vkWaitForFences(struct_vulkan->device.device, 1, &fence, VK_TRUE, UINT64_MAX);
  vkResetFences(struct_vulkan->device.device, 1, &fence);

  //---------------------------
}

}
