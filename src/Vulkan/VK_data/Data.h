#pragma once

namespace vk::data{class Buffer;}
namespace vk::image{class Texture;}
namespace vk::command{class Command_buffer;}
namespace vk::binding{class Descriptor;}
namespace vk{class Structure;}
namespace vk::structure{class Object;}
namespace vk::structure{class Pipeline;}
namespace vk::instance{class UID;}
namespace vk::synchro{class Synchro;}
namespace vk::binding{class Uniform;}
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
  void clean();
  void insert(utl::base::Data& data, utl::base::Pose* pose = nullptr);
  void remove(utl::base::Data& data);

  //Subfunction
  void update_vk_object(utl::base::Data& data, vk::structure::Object* vk_object);
  void create_vk_object(utl::base::Data& data, utl::base::Pose* pose);
  void clean_vk_object(vk::structure::Object* vk_object);
  void check_data(vk::structure::Object* vk_object);

private:
  vk::Structure* vk_struct;
  vk::data::Buffer* vk_buffer;
  vk::image::Texture* vk_texture;
  vk::command::Command_buffer* vk_command_buffer;
  vk::binding::Descriptor* vk_descriptor;
  vk::instance::UID* vk_uid;
  vk::synchro::Synchro* vk_synchro;
  vk::binding::Uniform* vk_uniform;
};

}
