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
  std::vector<vk::queue::structure::Family>& vec_queue_family = vk_struct->device.physical_device.vec_queue_family;
  vk::queue::structure::Set& set = vk_struct->device.queue;
  //---------------------------

  for(int i=0; i<vec_queue_family.size(); i++){
    vk::queue::structure::Family& family = vec_queue_family[i];

    if(family.capable_graphics && set.graphics.family_ID == -1){
      set.graphics.family_ID = i;
      set.graphics.family_index = family.current_index++;
      family.vec_queue.push_back(&set.graphics);
      family.vec_priority.push_back(1.0);
      break;
    }
  }

  //---------------------------
}
void Assignment::assign_presentation_queue(){
  std::vector<vk::queue::structure::Family>& vec_queue_family = vk_struct->device.physical_device.vec_queue_family;
  vk::queue::structure::Set& set = vk_struct->device.queue;
  //---------------------------

  for(int i=0; i<vec_queue_family.size(); i++){
    vk::queue::structure::Family& family = vec_queue_family[i];

    if(family.capable_presentation && set.presentation.family_ID == -1){
      set.presentation.family_ID = i;
      set.presentation.family_index = family.current_index++;
      family.vec_queue.push_back(&set.presentation);
      family.vec_priority.push_back(1.0);
      break;
    }
  }

  //---------------------------
}
void Assignment::assign_transfer_queue(){
  std::vector<vk::queue::structure::Family>& vec_queue_family = vk_struct->device.physical_device.vec_queue_family;
  vk::queue::structure::Set& set = vk_struct->device.queue;
  //---------------------------

  for(int i=0; i<vec_queue_family.size(); i++){
    vk::queue::structure::Family& family = vec_queue_family[i];

    if(family.capable_transfer && set.transfer.family_ID == -1){
      set.transfer.family_ID = i;
      set.transfer.family_index = family.current_index++;
      family.vec_queue.push_back(&set.transfer);
      family.vec_priority.push_back(1.0);
      break;
    }
  }

  //---------------------------
}
void Assignment::check_proper_assigment(){
  vk::queue::structure::Set& set = vk_struct->device.queue;
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
  if(set.presentation.family_ID == -1 && !vk_struct->param.headless){
    std::cout<<"[error] in presentation queue family assigment"<<std::endl;
    exit(0);
  }

  //---------------------------
}

}
