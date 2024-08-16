#pragma once

#include <Dynamic/src/Structure/Operation.h>
#include <Dynamic/src/Structure/Recorder.h>
#include <Dynamic/src/Structure/Colorization.h>


namespace dyn::prc{

struct Structure{
  //---------------------------

  dyn::recorder::Structure recorder;
  dyn::operation::Structure operation;
  dyn::colorization::Structure colorization;

  //---------------------------
};

}
