#include "Data.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::interface{

//Constructor / Destructor
Data::Data(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_texture = new vk::texture::Data(vk_struct);
  this->vk_data = new vk::data::Data(vk_struct);
  this->vk_render = new vk::gui::Render(vk_struct);

  //---------------------------
}
Data::~Data(){}

//Main function
ImTextureID Data::query_render_texture(){
  return vk_render->query_render_texture();
}
void Data::insert_data(std::shared_ptr<utl::base::Data> data, std::shared_ptr<utl::base::Pose> pose){
  vk_data->insert(data, pose);
}
void Data::remove_data(utl::base::Data& data){
  vk_data->remove(data);
}
void Data::insert_texture(utl::base::Data& data, std::shared_ptr<utl::media::Image> image){
  vk_texture->insert_texture(data, image);
}

}
