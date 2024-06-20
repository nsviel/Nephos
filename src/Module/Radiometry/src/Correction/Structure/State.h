#pragma once


namespace rad::correction::detection{

enum Step{
  WAIT_VALIDATION = 1,
  PROCESSING = 2,
};

}

namespace rad::correction::measure{

enum Step{
  WAIT_VALIDATION = 1,
  PROCESSING = 2,
};

}

namespace rad::correction{

enum State{
  NO_DATA = 0,
  HAS_DATA = 3,
};

}

namespace rad::correction::structure{

struct State{
  //---------------------------

  int detection = rad::correction::detection::WAIT_VALIDATION;
  int measure = rad::correction::measure::WAIT_VALIDATION;
  int data = rad::correction::NO_DATA;

  //---------------------------
};

}
