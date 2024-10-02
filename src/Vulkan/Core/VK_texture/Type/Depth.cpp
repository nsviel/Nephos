#include "Depth.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::texture{

//Constructor / Destructor
Depth::Depth(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_ressource = new vk::texture::Ressource(vk_struct);
  this->vk_retriever = new vk::data::Retriever(vk_struct);

  //---------------------------
}
Depth::~Depth(){}

//Main function
void Depth::insert_depth(utl::base::Data& data, std::shared_ptr<utl::base::Depth> depth){
  //---------------------------

  //Retrieve data vk object
  auto vk_object = vk_retriever->retrieve_vk_object(data);
  if(!vk_object) return;

  //Insert in vk object
  this->insert_image(*vk_object, depth);

  //---------------------------
}
void Depth::insert_depth(vk::structure::Object& vk_object, std::shared_ptr<utl::base::Depth> depth){
  if(!vk_ressource->check_texture(depth)) return;
  //---------------------------

  //Check if image already inserted
  auto vk_texture = vk_retriever->retrieve_vk_texture(vk_object, depth->name);
  if(vk_texture) return;

  //Create texture from depth and insert
  auto texture = std::make_shared<vk::structure::Texture>();
  texture->depth = depth;
  vk_ressource->create_texture(*texture);
  vk_object.map_texture[depth->name] = texture;

  //---------------------------
}

}
