#include "Headless.h"

#include <Vulkan/Namespace.h>


namespace vk::draw{

//Constructor / Destructor
Headless::Headless(vk::structure::Vulkan* vk_struct) : vk::draw::Drawer(vk_struct){
  //---------------------------


  //---------------------------
}
Headless::~Headless(){}

//Main function
void Headless::draw_frame(){
  //---------------------------

  vk::structure::Semaphore* semaphore;

  //Renderpass
  vector<vk::structure::Command*> vec_command;
  for(int i=0; i<vk_struct->render.vec_renderpass.size(); i++){
    vk::structure::Renderpass* renderpass = vk_struct->render.vec_renderpass[i];

    //Create command
    vk::structure::Command* command = new vk::structure::Command();
    if(i>0)command->vec_semaphore_processing.push_back(semaphore->end);

    //Run renderpass
    vk_render->run_renderpass(renderpass);

    //Complete and submit command with semaphore
    semaphore = vk_semaphore->query_free_semaphore();
    command->vec_command_buffer.push_back(renderpass->command_buffer);
    command->vec_semaphore_done.push_back(semaphore->end);
    command->vec_wait_stage.push_back(VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT);
    vec_command.push_back(command);
  }

  //Submission
  vk_struct->queue.graphics->add_graphics(vec_command);

  //---------------------------
}

}
