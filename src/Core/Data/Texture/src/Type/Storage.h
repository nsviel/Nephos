#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <string>

namespace dat::img{class Node;}
namespace dat::elm{class UID;}
namespace dat::base{class Entity;}
namespace vk::interface{class Texture;}
namespace utl::base{class Storage;}


namespace dat::img{

class Storage
{
public:
  //Constructor / Destructor
  Storage(dat::img::Node* node_image);
  ~Storage();

public:
  //Main function
  void add_storage(dat::base::Entity& entityy, std::shared_ptr<utl::base::Storage> storage);

  //Subfunction
  void insert_storage(dat::base::Entity& entity, std::shared_ptr<utl::base::Storage> storage);
  std::shared_ptr<utl::base::Storage> get_storage(dat::base::Entity& entity, std::string name);
  std::shared_ptr<utl::base::Storage> get_or_create_storage(dat::base::Entity& entity, std::string name);

private:
  vk::interface::Texture* vk_texture;
  dat::elm::UID* dat_uid;
};

}
