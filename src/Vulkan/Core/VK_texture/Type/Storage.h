#pragma once

#include <vulkan/vulkan.h>
#include <memory>

namespace vk{class Structure;}
namespace vk::texture{class Ressource;}
namespace vk::data{class Retriever;}


namespace vk::texture{

class Storage
{
public:
  //Constructor / Destructor
  Storage(vk::Structure* vk_struct);
  ~Storage();

public:
  //Main function


private:
  vk::Structure* vk_struct;
  vk::texture::Ressource* vk_ressource;
  vk::data::Retriever* vk_retriever;
};

}
