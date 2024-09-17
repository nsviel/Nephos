#pragma once

namespace vk{class Structure;}
namespace vk::structure{class Pipeline;}


namespace vk::pipeline{

class Vertex
{
public:
  //Constructor / Destructor
  Vertex(vk::Structure* vk_struct);
  ~Vertex();

public:
  //Main function
  void pipeline_vertex_description(vk::structure::Pipeline& pipeline);

  //subfunction
  void add_vertex_xyz(vk::structure::Pipeline& pipeline);
  void add_vertex_rgba(vk::structure::Pipeline& pipeline);
  void add_vertex_uv(vk::structure::Pipeline& pipeline);

private:
  vk::Structure* vk_struct;
};

}
