#pragma once

#include <memory>
#include <string>

namespace dat::elm{class Node;}
namespace dat::elm{class Entity;}
namespace dat::elm{class Set;}
namespace dat::base{class Entity;}
namespace dat::base{class Glyph;}
namespace dat::base{class Set;}
namespace dat::base{class Object;}


namespace dat::elm{

class Glyph
{
public:
  //Constructor / Destructor
  Glyph(dat::elm::Node* node_element);
  ~Glyph();

public:
  //Main function
  void insert_glyph(std::shared_ptr<dat::base::Set> set, std::shared_ptr<dat::base::Glyph> glyph);
  void insert_glyph(std::shared_ptr<dat::base::Entity> entity, std::shared_ptr<dat::base::Glyph> glyph);
  void insert_glyph(std::shared_ptr<dat::base::Entity> entity);

  //Update function
  void update_glyph(std::shared_ptr<dat::base::Entity> entity);
  void update_glyph(std::shared_ptr<dat::base::Object> object, int type);

  //Subfunction
  void create_glyph(std::shared_ptr<dat::base::Glyph> glyph);

private:
  dat::elm::Entity* dat_entity;
  dat::elm::Set* dat_set;
};

}
