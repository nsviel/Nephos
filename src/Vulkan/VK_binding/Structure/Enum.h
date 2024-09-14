#pragma once


namespace vk::binding{

enum Descriptor{
  LOCATION = 0,
  COLOR = 1,
  UV = 2,
  NORMAL = 2,
  DEPTH = 2,
};

enum Location{
  MVP = 0,
  WIDTH = 1,
};

}
