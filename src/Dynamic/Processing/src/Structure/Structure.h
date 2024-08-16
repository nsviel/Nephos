#pragma once

#include <Processing/src/Structure/Operation.h>
#include <Processing/src/Structure/Recorder.h>
#include <Processing/src/Structure/Colorization.h>


namespace dyn::prc{

struct Structure{
  //---------------------------

  dyn::prc::recorder::Structure recorder;
  dyn::prc::operation::Structure operation;
  dyn::prc::colorization::Structure colorization;

  //---------------------------
};

}
