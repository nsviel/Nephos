#pragma once

#include <Utility/Base/Type/Data.h>
#include <Utility/Base/Type/Pose.h>
#include <Utility/Base/Type/Element.h>
#include <Utility/Base/Media/Image.h>
#include <image/IconsFontAwesome6.h>

namespace dat::base{class Glyph;}
namespace dat::base{class Set;}


namespace dat::base{

struct Entity : public utl::base::Element{
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
  virtual utl::base::Pose* get_pose(){return &pose;}
  virtual utl::base::Data* get_data(){return &data;}
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
  utl::base::Pose pose;
  utl::base::Data data;
  std::list<dat::base::Glyph*> list_glyph;
  std::list<utl::media::Image*> list_image;

  //---------------------------
};

}
