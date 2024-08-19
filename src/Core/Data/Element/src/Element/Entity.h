#pragma once

#include <string>

namespace dat::elm{class Node;}
namespace dat::elm{class UID;}
namespace dat::base{class Entity;}
namespace vk::data{class Data;}
namespace dat::atr{class Location;}


namespace dat::elm{

class Entity
{
public:
  //Constructor / Destructor
  Entity(dat::elm::Node* node_element);
  ~Entity();

public:
  //Main function
  void init_entity(dat::base::Entity* entity);
  void remove_entity(dat::base::Entity* entity);
  void reset_pose(dat::base::Entity* entity);
  void visibility_entity(dat::base::Entity* entity, bool value);
  void update_data(dat::base::Entity* entity);

private:
  vk::data::Data* vk_data;
  dat::elm::UID* dat_uid;
  dat::atr::Location* atr_location;
};

}
