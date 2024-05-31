#pragma once

#include <string>

namespace dat{class Node;}
namespace dat{class Glyph;}
namespace dat{class Structure;}
namespace dat::base{class Entity;}
namespace dat::base{class Object;}
namespace vk::main{class Engine;}
namespace eng{class Node;}
namespace sce{class Operation;}
namespace utl::media{class Image;}



namespace dat{

class Entity
{
public:
  //Constructor / Destructor
  Entity(dat::Node* node_data);
  ~Entity();

public:
  //Main function
  void init_entity(dat::base::Entity* entity);
  void clear_entity(dat::base::Entity* entity);
  void update_data(dat::base::Entity* entity);
  void update_glyph(dat::base::Object* object);

private:
  eng::Node* node_engine;
  vk::main::Engine* vk_engine;
  dat::Glyph* dat_glyph;
  dat::Structure* dat_struct;
};

}
