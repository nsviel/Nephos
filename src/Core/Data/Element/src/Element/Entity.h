#pragma once

#include <string>
#include <memory>

namespace dat::elm{class Node;}
namespace dat::elm{class UID;}
namespace dat::base{class Entity;}
namespace dat::atr{class Location;}
namespace vk{class Interface;}


namespace dat::elm{

class Entity
{
public:
  //Constructor / Destructor
  Entity(dat::elm::Node* node_element);
  ~Entity();

public:
  //Main function
  void init_entity(std::shared_ptr<dat::base::Entity> entity);
  void remove_entity(std::shared_ptr<dat::base::Entity> entity);
  void reset_pose(std::shared_ptr<dat::base::Entity> entity);
  void visibility_entity(std::shared_ptr<dat::base::Entity> entity, bool value);
  void update_data(std::shared_ptr<dat::base::Entity> entity);

private:
  vk::Interface* vk_interface;
  dat::elm::UID* dat_uid;
  dat::atr::Location* atr_location;
};

}
