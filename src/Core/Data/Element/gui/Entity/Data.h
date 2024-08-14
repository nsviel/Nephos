#pragma once

#include <string>

namespace dat::elm{class Node;}
namespace dat::elm{class Entity;}
namespace dat::base{class Entity;}
namespace ope{class Operation;}


namespace dat::gui::entity{

class Data
{
public:
  //Constructor / Destructor
  Data(dat::elm::Node* node_element);
  ~Data();

  //Main function
  void draw_entity_data(dat::base::Entity* entity);

  //Parameter
  void entity_info(dat::base::Entity* entity);
  void entity_data(dat::base::Entity* entity);
  void entity_pose(dat::base::Entity* entity);

private:
  dat::elm::Entity* dat_entity;
  ope::Operation* ope_operation;

  int item_width;
};

}
