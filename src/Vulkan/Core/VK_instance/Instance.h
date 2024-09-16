#pragma once

namespace vk::validation{class Layer;}
namespace vk{class Structure;}


namespace vk::instance{

class Instance
{
public:
  //Constructor / Destructor
  Instance(vk::Structure* vk_struct);
  ~Instance();

public:
  //Main function
  void init();
  void clean();

  //Subfunction
  void create_instance();

private:
  vk::validation::Layer* vk_validation;
  vk::Structure* vk_struct;
};

}
