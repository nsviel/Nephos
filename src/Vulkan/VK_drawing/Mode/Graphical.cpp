#include "Graphical.h"

#include <Utility/Namespace.h>
#include <Vulkan/Namespace.h>


namespace vk::draw{

//Constructor / Destructor
Graphical::Graphical(vk::Structure* vk_struct) : vk::draw::Drawer(vk_struct){
  //---------------------------

  this->vk_transfer = new vk::memory::Transfer(vk_struct);
  this->utl_chrono = new utl::timer::Chrono();

  //---------------------------
}
Graphical::~Graphical(){}

//Main function
void Graphical::draw_frame(){
  //---------------------------

  //Init
  std::vector<vk::structure::Command*> vec_command;
  vk::synchro::structure::Semaphore semaphore = *vk_semaphore->query_free_semaphore();

  //Acquiere image
  bool sucess = acquire_image(semaphore);
  if(!sucess) return;

  //Rendering
  this->record_renderpass(vec_command, semaphore);
  this->copy_to_swapchain(vec_command, semaphore);
  this->submit_presentation(vec_command);

  //---------------------------
}

//Subfunction
bool Graphical::acquire_image(vk::synchro::structure::Semaphore& semaphore){
  //---------------------------

  //Acquire next image
  vk_struct->queue.graphics->wait_for_idle();
  vk_struct->queue.presentation->wait_for_idle();
  bool sucess = vk_struct->queue.presentation->acquire_next_image(semaphore.handle);

  //---------------------------
  return sucess;
}
void Graphical::record_renderpass(std::vector<vk::structure::Command*>& vec_command, vk::synchro::structure::Semaphore& semaphore){
  //---------------------------

  for(int i=0; i<vk_struct->render.vec_renderpass.size(); i++){
    vk::structure::Renderpass* renderpass = vk_struct->render.vec_renderpass[i];
    utl::timer::Timepoint ts = utl_chrono->start_t();

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
  vk::structure::Command_buffer* command_buffer = vk_transfer->copy_image_to_image(&renderpass->framebuffer->color, &vk_struct->swapchain.vec_frame[vk_struct->swapchain.current_ID]->color);
  vk::structure::Command* command = new vk::structure::Command();
  command->semaphore_wait = semaphore.handle;
  command->wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  command->command_buffer = command_buffer;
  semaphore = *vk_semaphore->query_free_semaphore();
  command->semaphore_done = semaphore.handle;
  vec_command.push_back(command);

  //---------------------------
}
void Graphical::submit_presentation(std::vector<vk::structure::Command*>& vec_command){
  //---------------------------

  //Submission
  vk_struct->queue.graphics->add_presentation(vec_command);

  //---------------------------
}

}
