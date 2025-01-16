#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <string>

namespace dat::img{class Node;}
namespace dat::elm{class UID;}
namespace dat::base{class Entity;}
namespace vk::interface{class Texture;}
namespace utl::base{class Depth;}


namespace dat::img{

class Depth
{
public:
  //Constructor / Destructor
  Depth(dat::img::Node* node_image);
  ~Depth();

public:
  //Main function
  void add_depth(dat::base::Entity& entityy, std::shared_ptr<utl::base::Depth> depth);

  //Subfunction
  void insert_depth(dat::base::Entity& entity, std::shared_ptr<utl::base::Depth> depth);
  std::shared_ptr<utl::base::Depth> get_depth(dat::base::Entity& entity, std::string name);
  std::shared_ptr<utl::base::Depth> get_or_create_depth(dat::base::Entity& entity, std::string name);

private:
  vk::interface::Texture* vk_texture;
  dat::elm::UID* dat_uid;
};

}
