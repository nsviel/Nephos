#pragma once

#include <Utility/Base/Type/Data.h>
#include <Utility/Base/Type/Element.h>
#include <Utility/Base/Media/Image.h>
#include <image/IconsFontAwesome6.h>

namespace dat::base{class Glyph;}
namespace dat::base{class Set;}


namespace dat::base{

struct Entity : public utl::base::Element{
  //---------------------------

  //Function
  Entity(){}
  virtual ~Entity(){}
  virtual void clean(){}

  //Info
  bool is_suppressible = true;
  bool is_permanent = false;
  bool is_movable = true;
  bool is_selectable = true;
  std::string entity_type = "base";
  std::string icon = ICON_FA_FILE;

  //Data
  utl::base::Data data;
  dat::base::Set* set_parent = nullptr;
  std::list<dat::base::Glyph*> list_glyph;
  std::list<utl::media::Image*> list_image;

  //---------------------------
};

}
