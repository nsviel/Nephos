#pragma once

#include <memory>

namespace vk::data{class Buffer;}
namespace vk::texture{class Data;}
namespace vk::command{class Command_buffer;}
namespace vk::descriptor{class Descriptor_set;}
namespace vk{class Structure;}
namespace vk::structure{class Object;}
namespace vk::structure{class Pipeline;}
namespace vk::descriptor::structure{class Binding;}
namespace vk::instance{class UID;}
namespace vk::synchro{class Synchro;}
namespace vk::descriptor{class Uniform;}
namespace utl::base{class Data;}
namespace utl::base{class Pose;}


namespace vk::data{

class Object
{
public:
  //Constructor / Destructor
  Object(vk::Structure* vk_struct);
  ~Object();

public:
  //Main function
  void update_object(std::shared_ptr<utl::base::Data> data, vk::structure::Object& object);
  void create_object(std::shared_ptr<utl::base::Data> data, std::shared_ptr<utl::base::Pose> pose);
  void clean_object(std::shared_ptr<vk::structure::Object> object);
  std::shared_ptr<vk::structure::Object> retrieve_object(utl::base::Data& data);

private:
  vk::Structure* vk_struct;
  vk::data::Buffer* vk_buffer;
  vk::texture::Data* vk_texture;
  vk::command::Command_buffer* vk_command_buffer;
  vk::descriptor::Descriptor_set* vk_descriptor_set;
  vk::instance::UID* vk_uid;
  vk::synchro::Synchro* vk_synchro;
  vk::descriptor::Uniform* vk_uniform;
};

}
