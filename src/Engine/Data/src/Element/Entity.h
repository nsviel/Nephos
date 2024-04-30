#pragma once

namespace vk::main{class Engine;}
namespace eng{class Node;}
namespace sce{class Operation;}
namespace dat{class Node;}
namespace dat{class Glyph;}
namespace dat{class Structure;}
namespace dat::base{class Entity;}


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

private:
  eng::Node* node_engine;
  vk::main::Engine* vk_engine;
  dat::Glyph* dat_glyph;
  dat::Structure* dat_struct;
};

}
