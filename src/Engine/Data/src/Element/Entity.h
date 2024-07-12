#pragma once

#include <string>

namespace cam{class Node;}
namespace dat{class Node;}
namespace dat::graph{class UID;}
namespace dat{class Structure;}
namespace dat::base{class Entity;}
namespace dat::base{class Object;}
namespace dat::base{class Glyph;}
namespace vk::data{class Data;}
namespace eng{class Node;}
namespace sce{class Operation;}
namespace cam{class Control;}
namespace utl::media{class Image;}
namespace ope::attribut{class Location;}
namespace ope::attribut{class Attribut;}


namespace dat::element{

class Entity
{
public:
  //Constructor / Destructor
  Entity(dat::Node* node_data);
  ~Entity();

public:
  //Main function
  void init_entity(dat::base::Entity* entity);
  void remove_entity(dat::base::Entity* entity);
  void reset_pose(dat::base::Entity* entity);
  void visibility_entity(dat::base::Entity* entity, bool value);
  void update_data(dat::base::Entity* entity);
  void update_pose(dat::base::Entity* entity);

private:
  cam::Node* node_camera;
  eng::Node* node_engine;
  vk::data::Data* vk_data;
  dat::Structure* dat_struct;
  dat::graph::UID* dat_uid;
  cam::Control* cam_control;
  ope::attribut::Location* ope_location;
  ope::attribut::Attribut* ope_attribut;
};

}
