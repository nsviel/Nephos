#pragma once

#include <memory>

namespace vk{class Structure;}
namespace vk::data{class Object;}
namespace utl::base{class Data;}
namespace utl::base{class Pose;}


namespace vk::data{

class Data
{
public:
  //Constructor / Destructor
  Data(vk::Structure* vk_struct);
  ~Data();

public:
  //Main function
  void insert(std::shared_ptr<utl::base::Data> data, std::shared_ptr<utl::base::Pose> pose);
  void update(std::shared_ptr<utl::base::Data> data);
  void remove(utl::base::Data& data);
  void clean();

  //Subfunction
  bool is_present(std::shared_ptr<utl::base::Data> data);

private:
  vk::Structure* vk_struct;
  vk::data::Object* vk_object;
};

}
