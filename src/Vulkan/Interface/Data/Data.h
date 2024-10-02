#pragma once

#include <imgui/core/imgui.h>
#include <glm/glm.hpp>
#include <memory>

namespace vk{class Structure;}
namespace vk::data{class Data;}
namespace utl::base{class Data;}
namespace utl::base{class Pose;}


namespace vk::interface{

class Data
{
public:
  //Constructor / Destructor
  Data(vk::Structure* vk_struct);
  ~Data();

public:
  //Main function
  void insert_data(std::shared_ptr<utl::base::Data> data, std::shared_ptr<utl::base::Pose> pose);
  void remove_data(utl::base::Data& data);

private:
  vk::Structure* vk_struct;
  vk::data::Data* vk_data;
};

}
