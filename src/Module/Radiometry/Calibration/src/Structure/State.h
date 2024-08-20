#pragma once


namespace rad::cal::detection{

enum Step{
  WAIT_VALIDATION = 1,
  PROCESSING = 2,
};

}

namespace rad::cal::measure{

enum Step{
  WAIT_VALIDATION = 1,
  PROCESSING = 2,
};

}

namespace rad::cal{

enum State{
  NO_DATA = 0,
  HAS_DATA = 3,
};

}

namespace rad::cal::structure{

struct State{
  //---------------------------

  int detection = rad::cal::detection::WAIT_VALIDATION;
  int measure = rad::cal::measure::WAIT_VALIDATION;
  int data = rad::cal::NO_DATA;

  //---------------------------
};

}
