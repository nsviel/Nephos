#pragma once

#include <memory>

namespace vk{class Structure;}
namespace vk::data{class Buffer;}
namespace vk::data{class Vertex;}
namespace vk::texture{class Image;}
namespace vk::commandbuffer{class Pool;}
namespace vk::instance{class UID;}
namespace vk::synchro{class Synchro;}
namespace vk::descriptor{class Descriptor_set;}
namespace vk::descriptor{class Uniform;}
namespace vk::structure{class Object;}
namespace vk::structure{class Pipeline;}
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
  void create_object(std::shared_ptr<utl::base::Data> data, std::shared_ptr<utl::base::Pose> pose);
  void update_object(vk::structure::Object& object);
  void clean_object(std::shared_ptr<vk::structure::Object> object);

  //Subfunction
  std::shared_ptr<vk::structure::Object> retrieve_object(utl::base::Data& data);

private:
  vk::Structure* vk_struct;
  vk::data::Buffer* vk_buffer;
  vk::data::Vertex* vk_vertex;
  vk::texture::Image* vk_tex_image;
  vk::commandbuffer::Pool* vk_command_buffer;
  vk::descriptor::Descriptor_set* vk_descriptor_set;
  vk::instance::UID* vk_uid;
  vk::synchro::Synchro* vk_synchro;
  vk::descriptor::Uniform* vk_uniform;
};

}
