#pragma once

#include <memory>

namespace vk{class Structure;}
namespace vk::structure{class Object;}
namespace utl::base{class Data;}


namespace vk::data{

class Function
{
public:
  //Constructor / Destructor
  Function(vk::Structure* vk_struct);
  ~Function();

public:
  //Main function
  std::shared_ptr<vk::structure::Object> retrieve_vk_object(utl::base::Data& data);

private:
  vk::Structure* vk_struct;
};

}
