#include "Storage.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::texture{

//Constructor / Destructor
Storage::Storage(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_ressource = new vk::texture::Ressource(vk_struct);
  this->vk_retriever = new vk::data::Retriever(vk_struct);

  //---------------------------
}
Storage::~Storage(){}

//Main function
void Image::insert_storage(vk::structure::Object& vk_object, std::shared_ptr<utl::base::Storage> storage){
  if(!vk_ressource->check_image(storage)) return;
  //---------------------------

  //Check if image already inserted
  auto vk_texture = vk_retriever->retrieve_vk_texture(vk_object, image->name);
  if(vk_texture) return;

  //Create texture from image and insert
  auto texture = std::make_shared<vk::structure::Texture>();
  texture->UID = vk_uid->query_free_UID();
  texture->storage = storage;
  vk_ressource->create_texture(*texture);
  vk_object.map_texture[image->name] = texture;

  //---------------------------
}

}
