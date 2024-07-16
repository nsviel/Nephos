#pragma once


namespace ope::color{

enum Mode{
  RGB = 0,
  UNICOLOR = 1,
  NORMAL = 3,
  FIELD = 4,
  STRUCTURE = 5,
  HEATMAP = 6,
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
