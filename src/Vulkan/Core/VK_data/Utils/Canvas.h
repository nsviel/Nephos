#pragma once

namespace vk{class Structure;}
namespace vk::data{class Buffer;}
namespace vk::data{class Vertex;}
namespace vk::data{class Data;}


namespace vk::data{

class Canvas
{
public:
  //Constructor / Destructor
  Canvas(vk::Structure* vk_struct);
  ~Canvas();

public:
  //Main function
  void init();
  void clean();

private:
  vk::Structure* vk_struct;
  vk::data::Buffer* vk_buffer;
  vk::data::Vertex* vk_vertex;
  vk::data::Data* vk_data;
};

}
