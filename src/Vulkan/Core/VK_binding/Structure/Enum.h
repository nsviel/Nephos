#pragma once


//Uniform
namespace vk::uniform{

enum ID{
  MVP = 0,
  TOPOLOGY_WIDTH = 1,
  PARAMETER = 5,
};

}

//Sampler
namespace vk::sampler{

enum ID{
  COLOR = 10,
  DEPTH = 11,
};

}

//Storage
namespace vk::storage{

enum ID{
  DEPTH = 20,
  TABLE_XY = 21,
  CLOUD = 22,
};

}
