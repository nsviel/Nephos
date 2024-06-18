#pragma once

#include <Utility/Specific/Common.h>

namespace dyn{class Node;}
namespace dyn{class Structure;}
namespace dyn::cloud{class Operation;}
namespace dat::base{class Set;}
namespace dat::base{class Entity;}


namespace dyn::gui{

class Colorization
{
public:
  //Constructor / Destructor
  Colorization(dyn::Node* node_dynamic);
  ~Colorization();

public:
  //Main function
  void design_colorization(dat::base::Set* set);
  void update_entity(dat::base::Entity* entity);

  //Mode function
  void mode_rgb(dat::base::Entity* entity);
  void mode_unicolor(dat::base::Entity* entity);
  void mode_intensity(dat::base::Entity* entity);
  void mode_intensity_inv(dat::base::Entity* entity);
  void mode_intensity_cor(dat::base::Entity* entity);
  void mode_intensity_cal(dat::base::Entity* entity);
  void mode_normal(dat::base::Entity* entity);
  void mode_heatmap(dat::base::Entity* entity);
  void mode_structure(dat::base::Entity* entity);

  //Option function
  void option_heatmap(dat::base::Entity* entity);
  void option_intensity(dat::base::Entity* entity);
  void option_height(dat::base::Entity* entity);

private:
  dyn::cloud::Operation* dyn_operation;
  dyn::Structure* dyn_struct;

  bool update_color = false;
};

}
