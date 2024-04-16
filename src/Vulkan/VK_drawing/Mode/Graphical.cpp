#include "Graphical.h"

#include <Vulkan/Namespace.h>


namespace vk::draw{

//Constructor / Destructor
Graphical::Graphical(vk::structure::Vulkan* vk_struct) : vk::draw::Drawer(vk_struct){
  //---------------------------


  //---------------------------
}
Graphical::~Graphical(){}

//Main function
void Graphical::draw_frame(){
  //---------------------------

  //Acquire next image
  vk_struct->queue.graphics->wait_for_idle();
  vk_struct->queue.presentation->wait_for_idle();
  vk::structure::Semaphore* semaphore = vk_semaphore->query_free_semaphore();
  bool ok = vk_struct->queue.presentation->acquire_next_image(semaphore->handle);
  if(!ok) return;

  //Renderpass
  vector<vk::structure::Command*> vec_command;
  for(int i=0; i<vk_struct->render.vec_renderpass.size(); i++){
    vk::structure::Renderpass* renderpass = vk_struct->render.vec_renderpass[i];
    string name = "eng::rp::" + renderpass->name;
    vk_struct->profiler->tasker_main->task_begin(name);

    //Run renderpass
    vk_render->run_renderpass(renderpass);

    //Create command
    vk::structure::Command* command = new vk::structure::Command();
    command->semaphore_wait = semaphore->handle;
    command->wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    command->command_buffer = renderpass->command_buffer;
    semaphore = vk_semaphore->query_free_semaphore();
    command->semaphore_done = semaphore->handle;
    vec_command.push_back(command);

    vk_struct->profiler->tasker_main->task_end(name);
  }

  //Submission
  vk_struct->queue.graphics->add_presentation(vec_command);

  //---------------------------
}

//Subfunction
void Graphical::record_renderpass(vk::structure::Renderpass* renderpass, vk::structure::Semaphore* semaphore, vector<vk::structure::Command*>& vec_command){
  //---------------------------






  //---------------------------
}


}
