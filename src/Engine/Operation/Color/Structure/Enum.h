#pragma once


namespace ope::color{

enum Mode{
  RGB = 0,
  UNICOLOR = 1,
  INTENSITY = 2,
  INTENSITY_INV = 3,
  INTENSITY_COR = 4,
  INTENSITY_CAL = 5,
  LOCATION = 6,
  NORMAL = 7,
  INCIDENCE_ANGLE = 8,
  HEATMAP = 9,
  STRUCTURE = 10,
};

}

namespace ope::heatmap{

enum Mode{
  INTENSITY = 0,
  INTENSITY_COR = 1,
  INTENSITY_CAL = 2,
  INCIDENCE_ANGLE = 3,
  HEIGHT = 4,
  RANGE = 5,
};

}
