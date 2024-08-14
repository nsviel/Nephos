#pragma once

#include <string>

namespace dat{class Node;}
namespace dat::element{class Entity;}
namespace dat::element{class Set;}
namespace dat::base{class Entity;}
namespace dat::base{class Glyph;}
namespace dat::base{class Set;}
namespace dat::base{class Object;}


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
  void insert_glyph(dat::base::Entity* entity);

  //Update function
  void update_glyph(dat::base::Entity* entity);
  void update_glyph(dat::base::Object* object, int type);

  //Subfunction
  void create_glyph(dat::base::Glyph* glyph);

private:
  dat::Node* node_data;
  dat::element::Entity* dat_entity;
  dat::element::Set* dat_set;
};

}
