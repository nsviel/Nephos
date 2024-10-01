#include "Storage.h"

#include <Data/Texture/Namespace.h>
#include <Data/Element/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace dat::img{

//Constructor / Destructor
Storage::Storage(dat::img::Node* node_image){
  //---------------------------

  vk::Node* node_vulkan = node_image->get_node_vulkan();
  dat::elm::Node* node_element = node_image->get_node_element();

  this->vk_data = node_vulkan->get_vk_data();
  this->dat_uid = node_element->get_dat_uid();

  //---------------------------
}
Storage::~Storage(){}

//Main function
void Storage::add_image(dat::base::Entity& entity, std::shared_ptr<utl::base::Storage> image){
  utl::base::Data& data = *entity.data;
  //----------------------------

  if(image->size == 0) return;
  if(image->width == 0) return;
  if(image->height == 0) return;

  //Check if image already inseretd
  auto it = data.map_storage.find(image->name);
  if(it == data.map_storage.end()){
    this->insert_image(entity, image);
  }

  //----------------------------
}

//Subfunction
void Storage::insert_image(dat::base::Entity& entity, std::shared_ptr<utl::base::Storage> image){
  utl::base::Data& data = *entity.data;
  //----------------------------

  image->UID = dat_uid->generate_UID();
  data.map_storage[image->name] = image;
  vk_data->insert_image(data, image);

  //----------------------------
}
std::shared_ptr<utl::base::Storage> Storage::get_image(dat::base::Entity& entity, std::string query){
  utl::base::Data& data = *entity.data;
  //----------------------------

  auto it = data.map_storage.find(query);
  if(it != data.map_storage.end()) return it->second;

  //----------------------------
  return nullptr;
}
std::shared_ptr<utl::base::Storage> Storage::get_or_create_image(dat::base::Entity& entity, std::string query){
  utl::base::Data& data = *entity.data;
  //----------------------------

  //Search for already existing image with same type
  auto it = data.map_storage.find(query);
  if(it != data.map_storage.end()) return it->second;

  //Else create it
  std::shared_ptr<utl::base::Storage> image = std::make_shared<utl::base::Storage>(query);
  this->add_image(entity, image);

  //----------------------------
  return image;
}

}
