#pragma once

#include <LLMR/src/Structure/Terminal.h>
#include <LLMR/src/Structure/Websocket.h>


namespace llmr{

struct Structure{
  //---------------------------

  llmr::structure::Terminal terminal;
  llmr::structure::Websocket wsok;

  //---------------------------
};

}
