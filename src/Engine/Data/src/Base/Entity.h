#pragma once

#include <Utility/Base/Type/Data.h>
#include <Utility/Base/Type/Pose.h>
#include <Utility/Base/Type/Element.h>
#include <Utility/Base/Media/Image.h>
#include <image/IconsFontAwesome6.h>

namespace dat::base{class Glyph;}
namespace dat::base{class Set;}


namespace dat::base{

struct Entity : public utl::type::Element{
  //---------------------------

  Entity();
  virtual ~Entity();
  virtual void init(){}
  virtual void reset(){}
  virtual void remove(){}
  virtual void info(){}
  virtual void update_data(){}
  virtual void update_pose(){}
  virtual void set_visibility(bool value){data.is_visible = value;}
  virtual utl::type::Pose* get_pose(){return &pose;}
  virtual utl::type::Data* get_data(){return &data;}
  void bind_image(utl::media::Image* image); // A virer

  //Info
  bool is_suppressible = true;
  bool is_permanent = false;
  bool is_movable = true;
  bool is_visible = true;
  std::string entity_type = "base";
  std::string icon = ICON_FA_FILE;
  dat::base::Set* set_parent = nullptr;

  //Data
  utl::type::Pose pose;
  utl::type::Data data;
  std::list<dat::base::Glyph*> list_glyph;
  std::list<utl::media::Image*> list_image;

  //---------------------------
};

}
