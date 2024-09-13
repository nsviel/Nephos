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
  void add_uniform(vk::binding::structure::Descriptor& descriptor);


  void create_uniform_buffers(vk::binding::structure::Binding& binding);
  void clean_uniform(vk::binding::structure::Binding& binding);
  void update_uniform(vk::binding::structure::Binding& binding);

  //uniform update
  template <typename T> void update_uniform(std::string uniform_name, vk::binding::structure::Binding& binding, T value);

  //Subfunction
  vk::binding::structure::Descriptor uniform_point_size();
  vk::binding::structure::Descriptor uniform_mvp();
  vk::binding::structure::Descriptor uniform_edl();

private:
  vk::Structure* vk_struct;
  vk::memory::Allocator* vk_mem_allocator;
};

}