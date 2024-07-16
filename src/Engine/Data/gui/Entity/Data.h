#pragma once

#include <string>

namespace dat{class Node;}
namespace dat::element{class Entity;}
namespace dat::base{class Entity;}
namespace ope{class Operation;}


namespace dat::gui::entity{

class Data
{
public:
  //Constructor / Destructor
  Data(dat::Node* node_data);
  ~Data();

  //Main function
  void draw_entity_data(dat::base::Entity* entity);

  //Parameter
  void entity_info(dat::base::Entity* entity);
  void entity_data(dat::base::Entity* entity);
  void entity_pose(dat::base::Entity* entity);

private:
  dat::element::Entity* dat_entity;
  ope::Operation* ope_operation;

  int item_width;
};

}
