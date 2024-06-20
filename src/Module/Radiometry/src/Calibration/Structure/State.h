#pragma once


namespace rad::calibration::detection{

enum Step{
  WAIT_VALIDATION = 1,
  PROCESSING = 2,
};

}

namespace rad::calibration::measure{

enum Step{
  WAIT_VALIDATION = 1,
  PROCESSING = 2,
};

}

namespace rad::calibration{

enum State{
  NO_DATA = 0,
  HAS_DATA = 3,
};

}

namespace rad::calibration::structure{

struct State{
  //---------------------------

  int detection = rad::calibration::detection::WAIT_VALIDATION;
  int measure = rad::calibration::measure::WAIT_VALIDATION;
  int data = rad::calibration::NO_DATA;

  //---------------------------
};

}
