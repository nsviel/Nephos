#pragma once

#include <Utility/Specific/Common.h>

namespace vk::main{class Engine;}
namespace dat{class Node;}
namespace dat{class Glyph;}
namespace eng{class Node;}
namespace sce{class Operation;}
namespace dat{class Database;}


namespace dat{

class Entity
{
public:
  //Constructor / Destructor
  Entity(dat::Node* node_data);
  ~Entity();

public:
  //Main function
  void init_entity(utl::type::Entity* entity);
  void clear_entity(utl::type::Entity* entity);

private:
  eng::Node* node_engine;
  vk::main::Engine* vk_engine;
  dat::Database* dat_database;
  dat::Glyph* dat_glyph;
};

}
