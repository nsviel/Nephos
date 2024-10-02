#include "Descriptor.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>
#include <random>


namespace vk::pipeline{

//Constructor / Destructor
Descriptor::Descriptor(vk::Structure* vk_struct){
  //---------------------------

  this->vk_uniform = new vk::descriptor::Uniform(vk_struct);
  this->vk_sampler = new vk::descriptor::Sampler(vk_struct);
  this->vk_layout = new vk::descriptor::Layout(vk_struct);
  this->vk_descriptor_set = new vk::descriptor::Descriptor_set(vk_struct);

  //---------------------------
}
Descriptor::~Descriptor(){}

//Main function
void Descriptor::create_pipeline_descriptor(vk::structure::Pipeline& pipeline){
  //---------------------------

  vk_layout->create_layout(pipeline.descriptor.layout);
  this->create_descriptor_set_pool(pipeline);

  //---------------------------
}
void Descriptor::clean_pipeline_descriptor(vk::structure::Pipeline& pipeline){
  //---------------------------

  this->clean_descriptor_set_pool(pipeline);
  vk_layout->clean_layout(pipeline.descriptor.layout);

  //---------------------------
}

//Subfunction
void Descriptor::create_descriptor_set_pool(vk::structure::Pipeline& pipeline){
  vk::pool::structure::Descriptor_set& pool = pipeline.descriptor.pool;
  //---------------------------

  //Number of command buffer
  pool.size = 50;

  //Descriptor set pool
  for(int i=0; i<pool.size; i++){
    //Create descriptor set
    std::shared_ptr<vk::structure::Descriptor_set> descriptor_set = std::make_shared<vk::structure::Descriptor_set>();
    vk_descriptor_set->allocate_descriptor_set(*descriptor_set, pipeline.descriptor.layout);

    //Store it in tank
    pool.tank.push_back(descriptor_set);
  }

  //---------------------------
}
void Descriptor::clean_descriptor_set_pool(vk::structure::Pipeline& pipeline){
  vk::pool::structure::Descriptor_set& pool = pipeline.descriptor.pool;
  //---------------------------

  //Clear all old command buffer
  for(auto& descriptor_set : pool.tank){
    vk_descriptor_set->clean_descriptor_set(*descriptor_set);
  }

  //---------------------------
}
std::shared_ptr<vk::structure::Descriptor_set> Descriptor::query_descriptor_set(vk::structure::Pipeline& pipeline){
  vk::pool::structure::Descriptor_set& pool = pipeline.descriptor.pool;
  //---------------------------

  // Random number generator setup
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distr(0, pool.size - 1);

  // Find a random available and unrecorded command buffer
  int index;
  std::shared_ptr<vk::structure::Descriptor_set> descriptor_set;
  do{
    //Get a random index
    index = distr(gen);
    descriptor_set = pool.tank[index];

    //Lock and if available return index descriptor set
    std::lock_guard<std::mutex> lock(descriptor_set->mutex);
    if(descriptor_set->is_available){
      descriptor_set->is_available = false;
      return descriptor_set;
    }
  }while(true);

  //Error message
  std::cout<<"[error] not enough free descriptor set"<<std::endl;

  //---------------------------
  return nullptr;
}


}
