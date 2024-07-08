#include "Manager.h"

#include <Vulkan/Namespace.h>
#include <set>


namespace vk::device::queue{

//Constructor / Destructor
Manager::Manager(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Manager::~Manager(){}

//Main function
void Manager::create_queue(vk::queue::structure::Queue& queue){
  if(queue.family_ID == -1) return;
  //---------------------------

  vkGetDeviceQueue(vk_struct->device.handle, queue.family_ID, queue.family_index, &queue.handle);

  //---------------------------
}
void Manager::create_queue_info(std::vector<VkDeviceQueueCreateInfo>& vec_queue_info){
  std::vector<vk::queue::structure::Family>& vec_queue_family = vk_struct->device.physical_device.vec_queue_family;
  //---------------------------

  for(int i=0; i<vec_queue_family.size(); i++){
    vk::queue::structure::Family& family = vec_queue_family[i];
    if(family.vec_queue.size() == 0) continue;

    //Get set of queue index
    std::set<int> set_index;
    for(int j=0; j<family.vec_queue.size(); j++){
      vk::queue::structure::Queue* queue = family.vec_queue[j];
      set_index.insert(queue->family_index);
    }

    //Get associated priority vector
    std::vector<float> vec_priority;
    for(const auto& element : set_index){
      vec_priority.push_back(1.0f);
    }

    //Create queue info accordingly
    VkDeviceQueueCreateInfo queue_info{};
    queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_info.queueFamilyIndex = static_cast<uint32_t>(family.ID);
    queue_info.queueCount = set_index.size();
    queue_info.pQueuePriorities = vec_priority.data();

    vec_queue_info.push_back(queue_info);
  }

  //---------------------------
}

//Subfunction
bool Manager::suitability_for_presentation(vk::device::structure::Physical& physical_device){
  //---------------------------

  bool is_device_suitable = false;
  bool is_graphics_able = false;
  bool is_transfer_able = false;

  for(int i=0; i<physical_device.vec_queue_family.size(); i++){
    vk::queue::structure::Family& queue_family = physical_device.vec_queue_family[i];

    //Querying for graphics family
    if(queue_family.capable_graphics && queue_family.capable_presentation){
      is_graphics_able = true;
    }

    //Querying for transfer family
    if(queue_family.capable_transfer){
      is_transfer_able = true;
    }
  }

  if(is_graphics_able && is_transfer_able){
    is_device_suitable = true;
  }

  //---------------------------
  return is_device_suitable;
}
bool Manager::suitability_for_graphics(vk::device::structure::Physical& physical_device){
  //---------------------------

  bool is_device_suitable = false;
  bool is_graphics_able = false;
  bool is_transfer_able = false;

  for(int i=0; i<physical_device.vec_queue_family.size(); i++){
    vk::queue::structure::Family& queue_family = physical_device.vec_queue_family[i];

    //Querying for graphics family
    if(queue_family.capable_graphics){
      is_graphics_able = true;
    }

    //Querying for transfer family
    if(queue_family.capable_transfer){
      is_transfer_able = true;
    }
  }

  if(is_graphics_able && is_transfer_able){
    is_device_suitable = true;
  }

  //---------------------------
  return is_device_suitable;
}

}
