#pragma once

#include <Utility/Base/Data/Data.h>
#include <Utility/Base/Data/Element.h>
#include <Utility/Base/Media/Image.h>
#include <fontawesome/IconsFontAwesome6.h>
#include <string>
#include <list>

namespace dat::base{class Set;}
namespace dat::base{class Glyph;}


namespace dat::base{

struct Entity : public utl::base::Element{
  //---------------------------

  //Function
  Entity(){
    this->type = utl::element::ENTITY;
  }
  virtual ~Entity(){}
  virtual void clean(){}

  //Info
  bool is_suppressible = true;
  bool is_permanent = false;
  bool is_selectable = true;
  std::string icon = ICON_FA_FILE;

  //Data
  utl::base::Data data;
  dat::base::Set* set_parent = nullptr;
  std::list<dat::base::Glyph*> list_glyph;
  std::list<utl::media::Image*> list_image;

  //---------------------------
};

}