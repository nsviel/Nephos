#pragma once

#include <Vulkan/Core/VK_binding/Structure/Layout.h>
#include <iostream>
#include <cstring>
#include <string>
#include <any>

namespace vk::memory{class Allocator;}
namespace vk{class Structure;}
namespace vk::descriptor::structure{class Descriptor;}
namespace vk::descriptor::structure{class Layout;}
namespace vk::descriptor::structure{class Uniform;}


namespace vk::descriptor{

class Uniform
{
public:
  //Constructor / Destructor
  Uniform(vk::Structure* vk_struct);
  ~Uniform();

public:
  //Main function
  void create_uniform(vk::descriptor::structure::Layout& layout, vk::descriptor::structure::Descriptor& descriptor);
  void clean_uniform(vk::descriptor::structure::Layout& layout);

  //Subfunction
  template <typename T>
  void update_uniform(std::string name, vk::descriptor::structure::Layout& layout, T value){
    //---------------------------

    //Retrieve uniform to update
    auto it = layout.map_uniform.find(name);
    if(it == layout.map_uniform.end()){
      std::cout << "------------------------" << std::endl;
      std::cout << "[error] Update uniform -> name not recognized \033[1;31m" << name << "\033[0m" << std::endl;
      std::cout << "Existing uniform names: " << std::endl;

      for(auto& [name, uniform] : layout.map_uniform){
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