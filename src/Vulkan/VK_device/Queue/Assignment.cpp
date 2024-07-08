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
void Assignment::find_queue_family_composition(vk::device::structure::Physical& physical_device){
  //---------------------------

  uint32_t nb_queue_family = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(physical_device.handle, &nb_queue_family, nullptr);
  if(nb_queue_family == 0){
    throw std::runtime_error("[error] No queue families on selected GPU");
  }

  // Retrieve information about each queue family
  std::vector<VkQueueFamilyProperties> queue_families(nb_queue_family);
  vkGetPhysicalDeviceQueueFamilyProperties(physical_device.handle, &nb_queue_family, queue_families.data());

  // Count the number of each type of queue
  for(int i=0; i<nb_queue_family; i++){
    //Queue family properties
    vk::queue::structure::Family queue_family;
    queue_family.ID = i;
    queue_family.property = queue_families[i];
    queue_family.nb_queue = queue_family.property.queueCount;
    queue_family.capable_graphics = (queue_family.property.queueFlags & VK_QUEUE_GRAPHICS_BIT) ? true : false;
    queue_family.capable_compute = (queue_family.property.queueFlags & VK_QUEUE_COMPUTE_BIT) ? true : false;
    queue_family.capable_transfer = (queue_family.property.queueFlags & VK_QUEUE_TRANSFER_BIT) ? true : false;
    queue_family.capable_sparseBinding = (queue_family.property.queueFlags & VK_QUEUE_SPARSE_BINDING_BIT) ? true : false;

    //Presentation property
    if(!vk_struct->param.headless){
      VkBool32 presentation_supported = false;
      vkGetPhysicalDeviceSurfaceSupportKHR(physical_device.handle, i, vk_struct->window.surface, &presentation_supported);
      queue_family.capable_presentation = presentation_supported;
    }

    physical_device.vec_queue_family.push_back(queue_family);
  }

  //---------------------------
}
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
