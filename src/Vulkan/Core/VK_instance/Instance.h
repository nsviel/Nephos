#pragma once

namespace vk{class Structure;}
namespace vk::validation{class Layer;}
namespace vk::validation{class Messenger;}


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
  vk::Structure* vk_struct;
  vk::validation::Layer* vk_layer;
  vk::validation::Messenger* vk_messenger;
};

}
