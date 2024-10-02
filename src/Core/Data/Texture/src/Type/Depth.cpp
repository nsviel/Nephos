#include "Depth.h"

#include <Data/Texture/Namespace.h>
#include <Data/Element/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace dat::img{

//Constructor / Destructor
Depth::Depth(dat::img::Node* node_image){
  //---------------------------

  vk::Node* node_vulkan = node_image->get_node_vulkan();
  dat::elm::Node* node_element = node_image->get_node_element();

  this->vk_data = node_vulkan->get_vk_data();
  this->dat_uid = node_element->get_dat_uid();

  //---------------------------
}
Depth::~Depth(){}

//Main function
void Depth::add_depth(dat::base::Entity& entity, std::shared_ptr<utl::base::Depth> depth){
  utl::base::Data& data = *entity.data;
  //----------------------------

  if(depth->size == 0) return;
  if(depth->width == 0) return;
  if(depth->height == 0) return;

  //Check if depth already inseretd
  auto it = data.map_depth.find(depth->name);
  if(it == data.map_depth.end()){
    this->insert_depth(entity, depth);
  }

  //----------------------------
}

//Subfunction
void Depth::insert_depth(dat::base::Entity& entity, std::shared_ptr<utl::base::Depth> depth){
  utl::base::Data& data = *entity.data;
  //----------------------------

  depth->UID = dat_uid->generate_UID();
  data.map_depth[depth->name] = depth;
  //vk_data->insert_depth(data, depth);

  //----------------------------
}
std::shared_ptr<utl::base::Depth> Depth::get_depth(dat::base::Entity& entity, std::string query){
  utl::base::Data& data = *entity.data;
  //----------------------------

  auto it = data.map_depth.find(query);
  if(it != data.map_depth.end()) return it->second;

  //----------------------------
  return nullptr;
}
std::shared_ptr<utl::base::Depth> Depth::get_or_create_depth(dat::base::Entity& entity, std::string query){
  utl::base::Data& data = *entity.data;
  //----------------------------

  //Search for already existing depth with same type
  auto it = data.map_depth.find(query);
  if(it != data.map_depth.end()) return it->second;

  //Else create it
  std::shared_ptr<utl::base::Depth> depth = std::make_shared<utl::base::Depth>(query);
  this->add_depth(entity, depth);

  //----------------------------
  return depth;
}

}
