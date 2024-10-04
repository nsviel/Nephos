#include "Assignment.h"

#include <Vulkan/Namespace.h>
#include <set>


namespace vk::device::queue{

//Constructor / Destructor
Assignment::Assignment(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Assignment::~Assignment(){}

//Main function
void Assignment::assign_queue(){
  //---------------------------

  this->assign_graphics_queue();
  this->assign_presentation_queue();
  this->assign_transfer_queue();
  this->check_proper_assigment();

  //---------------------------
}

//Subfunction
void Assignment::assign_graphics_queue(){
  vk::structure::Queue_set& set = vk_struct->core.device.queue;
  //---------------------------

  int index = 0;
  for(auto& family : vk_struct->core.device.physical_device.vec_queue_family){
    if(family.capable_graphics && set.graphics.family_ID == -1){
      set.graphics.family_ID = index;
      set.graphics.family_index = family.current_index++;
      family.vec_queue.push_back(&set.graphics);
      family.vec_priority.push_back(1.0);
      break;
    }

    index++;
  }

  //---------------------------
}
void Assignment::assign_presentation_queue(){
  vk::structure::Queue_set& set = vk_struct->core.device.queue;
  //---------------------------

  int index = 0;
  for(auto& family : vk_struct->core.device.physical_device.vec_queue_family){
    if(family.capable_presentation && set.presentation.family_ID == -1){
      set.presentation.family_ID = index;
      set.presentation.family_index = family.current_index++;
      family.vec_queue.push_back(&set.presentation);
      family.vec_priority.push_back(1.0);
      break;
    }

    index++;
  }

  //---------------------------
}
void Assignment::assign_transfer_queue(){
  vk::structure::Queue_set& set = vk_struct->core.device.queue;
  //---------------------------

  int index = 0;
  for(auto& family : vk_struct->core.device.physical_device.vec_queue_family){
    if(family.capable_transfer && set.transfer.family_ID == -1){
      set.transfer.family_ID = index;
      set.transfer.family_index = family.current_index++;
      family.vec_queue.push_back(&set.transfer);
      family.vec_priority.push_back(1.0);
      break;
    }

    index++;
  }

  //---------------------------
}
void Assignment::check_proper_assigment(){
  vk::structure::Queue_set& set = vk_struct->core.device.queue;
  //---------------------------

  //check for good assigment
  if(set.graphics.family_ID == -1){
    std::cout<<"[error] in graphics queue family assigment"<<std::endl;
    exit(0);
  }
  if(set.transfer.family_ID == -1){
    std::cout<<"[error] in transfer queue family assigment"<<std::endl;
    exit(0);
  }
  if(set.presentation.family_ID == -1 && !vk_struct->interface.param.headless){
    std::cout<<"[error] in presentation queue family assigment"<<std::endl;
    exit(0);
  }

  //---------------------------
}

}
