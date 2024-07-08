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

void Assignment::find_queue_family_assigment(){
  //---------------------------

  std::vector<vk::queue::structure::Family>& vec_queue_family = vk_struct->device.physical_device.vec_queue_family;
  vk::queue::structure::Set& set = vk_struct->device.queue;

  for(int i=0; i<vec_queue_family.size(); i++){
    vk::queue::structure::Family& family = vec_queue_family[i];
    bool several_queue = family.nb_queue > 1;

    //Graphics
    if(family.capable_graphics && set.graphics.family_ID == -1){
      set.graphics.family_ID = i;
      set.graphics.family_index = several_queue ? family.current_index++ : 0;
      family.vec_queue.push_back(&set.graphics);
    }

    //Presentation
    if(family.capable_presentation && set.presentation.family_ID == -1){
      set.presentation.family_ID = i;
      set.presentation.family_index = several_queue ? family.current_index++ : 0;
      family.vec_queue.push_back(&set.presentation);
    }

    //Transfer
    if(family.capable_transfer && set.transfer.family_ID == -1){ // If transfer not assigned
      //Discrete GPU
      if(vk_struct->device.physical_device.discrete_gpu){
        if(i != set.graphics.family_ID && i==2){
          set.transfer.family_ID = i;
          set.transfer.family_index = several_queue ? family.current_index++ : 0;
          family.vec_queue.push_back(&set.transfer);
          break;
        }
      }
      //Integrated GPU
      else{
        set.transfer.family_ID = i;
        set.transfer.family_index = several_queue ? family.current_index++ : 0;
        family.vec_queue.push_back(&set.transfer);
      }
    }

  }

  //check for good assigment
  if(set.graphics.family_ID == -1){
    std::cout<<"[error] in graphics queue family assigment"<<std::endl;
  }
  if(set.transfer.family_ID == -1){
    std::cout<<"[error] in transfer queue family assigment"<<std::endl;
  }
  if(set.presentation.family_ID == -1 && !vk_struct->param.headless){
    std::cout<<"[error] in presentation queue family assigment"<<std::endl;
  }

  //---------------------------
}

}
