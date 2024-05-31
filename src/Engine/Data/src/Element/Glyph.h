#pragma once

#include <string>

namespace dat{class Node;}
namespace dat{class Entity;}
namespace dat{class Set;}
namespace dat::base{class Entity;}
namespace dat::base{class Glyph;}
namespace dat::base{class Set;}


namespace dat{

class Glyph
{
public:
  //Constructor / Destructor
  Glyph(dat::Node* node_data);
  ~Glyph();

public:
  //Main function
  void insert_glyph(dat::base::Set* set, dat::base::Glyph* glyph);
  void insert_glyph(dat::base::Entity* entity, dat::base::Glyph* glyph);
  void update_glyph(dat::base::Entity* entity);

private:
  dat::Node* node_data;
  dat::Entity* dat_entity;
  dat::Set* dat_set;
};

}
