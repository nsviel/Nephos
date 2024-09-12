#pragma once

namespace vk{class Structure;}
namespace vk::structure{class Subpass;}


namespace vk::render::pipeline{

class Factory
{
public:
  //Constructor / Destructor
  Factory(vk::Structure* vk_struct);
  ~Factory();

public:
  //Main function

private:
  vk::Structure* vk_struct;
};

}
