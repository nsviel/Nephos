#pragma once

#include <Utility/Specific/Common.h>

namespace rad::detection{class Node;}
namespace rad::detection{class Structure;}
namespace rad::detection::cloud{class Measure;}
namespace rad::detection::sphere{class Glyph;}
namespace dyn::base{class Sensor;}
namespace ope::fitting{class Sphere;}
namespace ope::fitting{class Ransac;}


namespace rad::detection::cloud{

class Ransac
{
public:
  //Constructor / Destructor
  Ransac(rad::detection::Node* node_detection);
  ~Ransac();

public:
  //Main function
  void ransac_sphere(dyn::base::Sensor* sensor);

  //Subfunction
  void reset_search_space();
  void reduce_search_space(dyn::base::Sensor* sensor);
  void apply_ransac();
  void process_measurement();

private:
  rad::detection::cloud::Measure* rad_measure;
  rad::detection::Structure* rad_struct;
  rad::detection::sphere::Glyph* rad_glyph;
  ope::fitting::Sphere* ope_fitting;
  ope::fitting::Ransac* ope_ransac;
};

}
