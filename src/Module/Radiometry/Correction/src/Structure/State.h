#pragma once


namespace rad::cor::detection{

enum Step{
  WAIT_VALIDATION = 1,
  PROCESSING = 2,
};

}

namespace rad::cor::measure{

enum Step{
  WAIT_VALIDATION = 1,
  PROCESSING = 2,
};

}

namespace rad::cor{

enum State{
  NO_DATA = 0,
  HAS_DATA = 1,
};

}

namespace rad::cor::structure{

struct State{
  //---------------------------

  int detection = rad::cor::detection::WAIT_VALIDATION;
  int measure = rad::cor::measure::WAIT_VALIDATION;
  int data = rad::cor::NO_DATA;

  //---------------------------
};

}
