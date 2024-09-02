#pragma once

#include <Utility/Base/Data/Element.h>
#include <fontawesome/IconsFontAwesome6.h>
#include <memory>
#include <string>
#include <list>

namespace dat::base{class Entity;}


namespace dat::base{

struct Set : public utl::base::Element{
  //---------------------------

  Set(){
    this->type = "set";
  }
  ~Set(){}
  virtual void reset(){}

  //Info
  std::string icon = ICON_FA_FOLDER;
  bool is_visible = true;
  bool is_locked = false;
  bool is_suppressible = false;
  bool is_open = true;
  int nb_entity = 0;
  int nb_subset = 0;

  //Data
  std::weak_ptr<dat::base::Entity> active_entity;
  std::weak_ptr<dat::base::Set> active_subset;
  std::weak_ptr<dat::base::Set> set_parent;
  std::list< std::shared_ptr<dat::base::Entity> > list_entity;
  std::list< std::shared_ptr<dat::base::Set> > list_subset;

  //---------------------------
};

}
