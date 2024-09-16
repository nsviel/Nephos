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
  void pipeline_vertex_description(vk::structure::Pipeline* pipeline);

  //subfunction
  void single_vertex_attribut(vk::structure::Pipeline* pipeline);
  void flow_vertex_binding(vk::structure::Pipeline* pipeline);

private:
  vk::Structure* vk_struct;
};

}
