#include "Graphical.h"

#include <Utility/Namespace.h>
#include <Vulkan/Namespace.h>


namespace vk::draw{

//Constructor / Destructor
Graphical::Graphical(vk::Structure* vk_struct) : vk::draw::Drawer(vk_struct){
  //---------------------------

  this->vk_transfer = new vk::memory::Transfer(vk_struct);
  this->vk_swapchain = new vk::presentation::Swapchain(vk_struct);
  this->utl_chrono = new sys::timer::Chrono();

  //---------------------------
}
Graphical::~Graphical(){}

//Main function
void Graphical::draw_frame(){
  //---------------------------

  vk_struct->queue.presentation->make_rendering();

  //---------------------------
}

//Subfunction
void Graphical::record_renderpass(std::vector<vk::structure::Command*>& vec_command, vk::synchro::structure::Semaphore& semaphore){
  //---------------------------

  for(int i=0; i<vk_struct->render.vec_renderpass.size(); i++){
    vk::structure::Renderpass* renderpass = vk_struct->render.vec_renderpass[i];
    sys::timer::Timepoint ts = utl_chrono->start_t();

    //Run renderpass
    vk_render->run_renderpass(renderpass);

    //Create command
    vk::structure::Command* command = new vk::structure::Command();
    command->semaphore_wait = semaphore.handle;
    command->wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    command->command_buffer = renderpass->command_buffer;
    semaphore = *vk_semaphore->query_free_semaphore();
    command->semaphore_done = semaphore.handle;
    vec_command.push_back(command);

    renderpass->duration = utl_chrono->stop_ms(ts);
  }

  //---------------------------
}
void Graphical::copy_to_swapchain(std::vector<vk::structure::Command*>& vec_command, vk::synchro::structure::Semaphore& semaphore){
  //---------------------------

  //Copy renderpass to swapchain image
  vk::structure::Renderpass* renderpass = vk_struct->render.get_renderpass_byName("gui");
  vk::structure::Command_buffer* command_buffer = vk_transfer->copy_image_to_image(renderpass->framebuffer->color, vk_struct->swapchain.vec_frame[vk_struct->swapchain.current_ID]->color);
  vk::structure::Command* command = new vk::structure::Command();
  command->semaphore_wait = semaphore.handle;
  command->wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  command->command_buffer = command_buffer;
  semaphore = *vk_semaphore->query_free_semaphore();
  command->semaphore_done = semaphore.handle;
  vec_command.push_back(command);

  //---------------------------
}

}
