#pragma once

#include <string>
#include <memory>

namespace dat::elm{class Node;}
namespace dat::elm{class UID;}
namespace dat::base{class Entity;}
namespace dat::atr{class Location;}
namespace vk::interface{class Data;}


namespace dat::elm{

class Entity
{
public:
  //Constructor / Destructor
  Entity(dat::elm::Node* node_element);
  ~Entity();

public:
  //Main function
  void init_entity(dat::base::Entity& entity);
  void remove_entity(dat::base::Entity& entity);
  void reset_pose(dat::base::Entity& entity);
  void visibility_entity(dat::base::Entity& entity, bool value);
  void update_data(dat::base::Entity& entity);

private:
  vk::interface::Data* vk_data;
  dat::elm::UID* dat_uid;
  dat::atr::Location* atr_location;
};

}
