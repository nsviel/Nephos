#pragma once

namespace vk{class Structure;}
namespace vk::descriptor{class Uniform;}
namespace vk::compute{class Pipeline;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Pipeline;}


namespace vk::compute::dtc{

class Recorder
{
public:
  //Constructor / Destructor
  Recorder(vk::Structure* vk_struct);
  ~Recorder();

public:
  //Main function
  void run_compute();

  //Subfunction
  void bind_pipeline(vk::structure::Pipeline& pipeline);
  void update_sampler(vk::structure::Pipeline& pipeline);

private:
  vk::Structure* vk_struct;
  vk::descriptor::Uniform* vk_uniform;
  vk::compute::Pipeline* vk_pipeline;
};

}
