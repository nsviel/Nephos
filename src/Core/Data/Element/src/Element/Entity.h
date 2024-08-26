#pragma once

#include <string>
#include <memory>

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
  void init_entity(std::shared_ptr<dat::base::Entity> entity);
  void remove_entity(std::shared_ptr<dat::base::Entity> entity);
  void reset_pose(std::shared_ptr<dat::base::Entity> entity);
  void visibility_entity(std::shared_ptr<dat::base::Entity> entity, bool value);
  void update_data(std::shared_ptr<dat::base::Entity> entity);

private:
  vk::data::Data* vk_data;
  dat::elm::UID* dat_uid;
  dat::atr::Location* atr_location;
};

}
