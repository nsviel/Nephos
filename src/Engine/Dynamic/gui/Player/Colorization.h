#pragma once

#include <Utility/Specific/Common.h>

namespace dat{class Selection;}
namespace dyn{class Node;}
namespace dyn{class Structure;}
namespace dyn::cloud{class Operation;}
namespace ope{class Operation;}
namespace ope::normal{class KNN;}
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

  //Subfunction
  void mode_rgb(dat::base::Entity* entity);
  void mode_unicolor(dat::base::Entity* entity);
  void mode_intensity(dat::base::Entity* entity);
  void mode_intensity_inv(dat::base::Entity* entity);
  void mode_normal(dat::base::Entity* entity);
  void mode_heatmap(dat::base::Entity* entity);
  void mode_structure(dat::base::Entity* entity);
  void draw_option(dat::base::Entity* entity);

private:
  dat::Selection* dat_selection;
  dyn::cloud::Operation* dyn_operation;
  dyn::Structure* dyn_struct;
  ope::Operation* ope_operation;
  ope::normal::KNN* ope_normal;

  bool update_color = false;
};

}
