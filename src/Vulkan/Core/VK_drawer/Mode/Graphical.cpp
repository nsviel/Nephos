#include "Graphical.h"

#include <Utility/Namespace.h>
#include <Vulkan/Namespace.h>


namespace vk::draw{

//Constructor / Destructor
Graphical::Graphical(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_transfer = new vk::memory::Transfer(vk_struct);
  this->vk_swapchain = new vk::presentation::Swapchain(vk_struct);
  this->utl_chrono = new sys::timer::Chrono();
  this->vk_render = new vk::draw::Renderer(vk_struct);
  this->vk_fence = new vk::synchro::Fence(vk_struct);
  this->vk_semaphore = new vk::synchro::Semaphore(vk_struct);

  //---------------------------
}
Graphical::~Graphical(){}

//Main function
void Graphical::draw_frame(){
  //---------------------------

  vk_struct->core.queue.presentation->make_rendering();

  //---------------------------
}

//Subfunction
void Graphical::record_renderpass(std::vector<std::unique_ptr<vk::structure::Command>>& vec_command, vk::synchro::structure::Semaphore& semaphore){
  //---------------------------

  for(auto& renderpass : vk_struct->render.renderpass.vec_renderpass){
    sys::timer::Timepoint ts = utl_chrono->start_t();

    //Run renderpass
    vk_render->run_renderpass(renderpass);

    //Create command
    std::unique_ptr<vk::structure::Command> command = std::make_unique<vk::structure::Command>();
    command->semaphore_wait = semaphore.handle;
    command->wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    command->command_buffer = renderpass->command_buffer;
    semaphore = *vk_semaphore->query_free_semaphore();
    command->semaphore_done = semaphore.handle;
    vec_command.push_back(std::move(command));

    renderpass->duration = utl_chrono->stop_ms(ts);
  }

  //---------------------------
}
void Graphical::copy_to_swapchain(std::vector<std::unique_ptr<vk::structure::Command>>& vec_command, vk::synchro::structure::Semaphore& semaphore){
  //---------------------------

  //Copy renderpass to swapchain image
  vk::structure::Renderpass& renderpass = vk_struct->render.renderpass.presentation;
  std::shared_ptr<vk::structure::Command_buffer> command_buffer = vk_transfer->copy_image_to_image(renderpass.framebuffer.color, vk_struct->core.swapchain.vec_frame[vk_struct->core.swapchain.current_ID]->color);

  std::unique_ptr<vk::structure::Command> command = std::make_unique<vk::structure::Command>();
  command->semaphore_wait = semaphore.handle;
  command->wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  command->command_buffer = command_buffer;
  semaphore = *vk_semaphore->query_free_semaphore();
  command->semaphore_done = semaphore.handle;
  vec_command.push_back(std::move(command));

  //---------------------------
}

}
