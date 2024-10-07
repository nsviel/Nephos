#pragma once

namespace vk{class Structure;}
namespace vk::memory{class Allocator;}
namespace vk::memory{class Transfer;}
namespace vk::structure{class Object;}
namespace vk::structure{class Buffer;}
namespace vk::structure{class Vertex;}


namespace vk::data{

class Buffer
{
public:
  //Constructor / Destructor
  Buffer(vk::Structure* vk_struct);
  ~Buffer();

public:
  //Main function
  void create_buffer(vk::structure::Vertex& vertex);
  void update_buffer(vk::structure::Vertex& vertex, void* data);
  void clean_buffer(vk::structure::Buffer& buffer);

private:
  vk::Structure* vk_struct;
  vk::memory::Allocator* vk_mem_allocator;
  vk::memory::Transfer* vk_mem_transfer;
};

}
