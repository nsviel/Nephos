#pragma once


namespace vk::queue{

enum Type{
  GRAPHICS = 0,
  PRESENTATION = 1,
  TRANSFER = 2,
};

enum State{
  WAIT_COMMAND = 0,
  SUBMIT_COMMAND = 1,
  PAUSED = 2,
};

}
