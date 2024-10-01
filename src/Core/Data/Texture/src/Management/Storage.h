#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <string>

namespace dat::img{class Node;}
namespace dat::elm{class UID;}
namespace dat::base{class Entity;}
namespace vk::interface{class Data;}
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
  void add_image(dat::base::Entity& entityy, std::shared_ptr<utl::base::Storage> image);

  //Subfunction
  void insert_image(dat::base::Entity& entity, std::shared_ptr<utl::base::Storage> image);
  std::shared_ptr<utl::base::Storage> get_image(dat::base::Entity& entity, std::string name);
  std::shared_ptr<utl::base::Storage> get_or_create_image(dat::base::Entity& entity, std::string name);

private:
  vk::interface::Data* vk_data;
  dat::elm::UID* dat_uid;
};

}
