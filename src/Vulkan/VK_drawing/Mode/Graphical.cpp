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
  vk::structure::Semaphore* semaphore = vk_semaphore->query_free_semaphore();
  bool ok = vk_struct->queue.presentation->acquire_next_image(semaphore->end);
  if(!ok) return;

  //Renderpass
  vector<vk::structure::Command*> vec_command;
  for(int i=0; i<vk_struct->render.vec_renderpass.size(); i++){
    vk::structure::Renderpass* renderpass = vk_struct->render.vec_renderpass[i];
    string name = "eng::rp::" + renderpass->name;
    vk_struct->profiler->tasker_main->task_begin(name);

    //Create command
    vk::structure::Command* command = new vk::structure::Command();
    command->vec_semaphore_processing.push_back(semaphore->end);

    //Run renderpass
    vk_render->run_renderpass(renderpass);

    //Complete and submit command with semaphore
    semaphore = vk_semaphore->query_free_semaphore();
    command->vec_command_buffer.push_back(renderpass->command_buffer);
    command->vec_semaphore_done.push_back(semaphore->end);
    command->vec_wait_stage.push_back(VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT);
    vec_command.push_back(command);

    vk_struct->profiler->tasker_main->task_end(name);
  }

  //Submission
  vk_struct->queue.graphics->add_presentation(vec_command);

  //---------------------------
}

//Subfunction
void Graphical::record_renderpass(vk::structure::Semaphore* semaphore, vector<vk::structure::Command*>& vec_command){
  //---------------------------

  int nb_renderpass = vk_struct->render.vec_renderpass.size();
  for(int i=0; i<nb_renderpass; i++){
    vk::structure::Renderpass* renderpass = vk_struct->render.vec_renderpass[i];
    string name = "eng::rp::" + renderpass->name;
    vk_struct->profiler->tasker_main->task_begin(name);

    //Create command
    vk::structure::Command* command = new vk::structure::Command();
    vec_command.push_back(command);
    command->vec_semaphore_processing.push_back(semaphore->end);

    //Run renderpass
    vk_render->run_renderpass(renderpass);

    //Complete and submit command with semaphore
    semaphore = vk_semaphore->query_free_semaphore();
    command->vec_command_buffer.push_back(renderpass->command_buffer);
    command->vec_semaphore_done.push_back(semaphore->end);
    command->vec_wait_stage.push_back(VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT);

    vk_struct->profiler->tasker_main->task_end(name);
  }

  //---------------------------
}


}
