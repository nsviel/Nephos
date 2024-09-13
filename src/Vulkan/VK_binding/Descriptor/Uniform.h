#pragma once

#include <string>

namespace vk::memory{class Allocator;}
namespace vk{class Structure;}
namespace vk::binding::structure{class Descriptor;}
namespace vk::binding::structure{class Binding;}
namespace vk::binding::structure{class Uniform;}


namespace vk::binding{

class Uniform
{
public:
  //Constructor / Destructor
  Uniform(vk::Structure* vk_struct);
  ~Uniform();

public:
  //Main function
  void create_uniform(vk::binding::structure::Binding& binding, vk::binding::structure::Descriptor& descriptor);
  void clean_uniform(vk::binding::structure::Binding& binding);
  void update_uniform(vk::binding::structure::Binding& binding);

  //Subfunction
  template <typename T> void update_uniform(std::string uniform_name, vk::binding::structure::Binding& binding, T value);

private:
  vk::Structure* vk_struct;
  vk::memory::Allocator* vk_mem_allocator;
};

}
