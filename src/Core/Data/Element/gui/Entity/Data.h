#pragma once

#include <memory>
#include <string>

namespace dat::elm{class Node;}
namespace dat::elm{class Entity;}
namespace dat::base{class Entity;}
namespace eng::trf{class Operation;}


namespace dat::entity::gui{

class Data
{
public:
  //Constructor / Destructor
  Data(dat::elm::Node* node_element);
  ~Data();

  //Main function
  void draw_entity_data(std::shared_ptr<dat::base::Entity> entity);

  //Parameter
  void entity_info(std::shared_ptr<dat::base::Entity> entity);
  void entity_data(std::shared_ptr<dat::base::Entity> entity);
  void entity_pose(std::shared_ptr<dat::base::Entity> entity);

private:
  dat::elm::Entity* dat_entity;
  eng::trf::Operation* trf_operation;

  int item_width;
};

}
