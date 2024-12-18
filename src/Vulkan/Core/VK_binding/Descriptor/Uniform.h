#pragma once

#include <Vulkan/Core/VK_binding/Structure/Descriptor_set.h>
#include <iostream>
#include <cstring>
#include <string>
#include <any>

namespace vk{class Structure;}
namespace vk::memory{class Allocator;}
namespace vk::structure{class Descriptor;}
namespace vk::structure{class Descriptor_set;}
namespace vk::structure{class Layout;}
namespace vk::structure{class Uniform;}


namespace vk::descriptor{

class Uniform
{
public:
  //Constructor / Destructor
  Uniform(vk::Structure* vk_struct);
  ~Uniform();

public:
  //Main function
  void create_descriptor(vk::structure::Descriptor_set& descriptor_set, vk::structure::Descriptor& descriptor);
  void actualize_uniform(vk::structure::Descriptor_set& descriptor_set);
  void clean_uniform(vk::structure::Descriptor_set& descriptor_set);

  //Subfunction
  template <typename T>
  void update_uniform(std::string name, vk::structure::Descriptor_set& descriptor_set, T value){
    //---------------------------

    //Retrieve uniform to update
    auto it = descriptor_set.map_uniform.find(name);
    if(it == descriptor_set.map_uniform.end()){
      std::cout << "------------------------" << std::endl;
      std::cout << "[error] Update uniform -> name not recognized \033[1;31m" << name << "\033[0m" << std::endl;
      std::cout << "Existing uniform names: " << std::endl;

      for(auto& [name, uniform] : descriptor_set.map_uniform){
        std::cout << "\033[1;32m" << name << "\033[0m" << std::endl;
      }

      std::cout << "------------------------" << std::endl;
      exit(0);
    }

    //Update uniform
    auto uniform = it->second;
    std::memcpy(uniform->mapped, &value, sizeof(value));

    //---------------------------
  }

private:
  vk::Structure* vk_struct;
  vk::memory::Allocator* vk_mem_allocator;
};

}
