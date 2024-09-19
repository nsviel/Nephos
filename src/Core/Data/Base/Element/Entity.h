#pragma once

#include <Utility/Base/Data/Data.h>
#include <Utility/Base/Data/Element.h>
#include <Utility/Base/Media/Image.h>
#include <fontawesome/IconsFontAwesome6.h>
#include <memory>
#include <string>
#include <list>

namespace dat::base{class Set;}
namespace dat::base{class Glyph;}


namespace dat::base{

struct Entity : public utl::base::Element{
  //---------------------------

  //Function
  Entity(){
    this->type = "entity";
  }
  virtual ~Entity(){}
  virtual void clean(){}

  //Info
  bool is_suppressible = true;
  bool is_permanent = false;
  bool is_selectable = true;
  std::string icon = ICON_FA_FILE;
  std::string type_entity = "";

  //Data
  std::weak_ptr<dat::base::Set>  set_parent;
  std::list< std::shared_ptr<dat::base::Glyph> > list_glyph;
  std::shared_ptr<utl::base::Data> data = std::make_shared<utl::base::Data>();

  //---------------------------
};

}
