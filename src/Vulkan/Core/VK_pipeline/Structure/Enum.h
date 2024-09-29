#pragma once


//Pipeline
namespace vk::pipeline{

enum Type{
  RENDER = 0,
  COMPUTE = 1,
};

}

//Data attribut name
namespace vk::attribut{

enum ID{
  XYZ = 0,
  RGBA = 1,
  UV = 2,
};

}

//Data attribut shader location
namespace vk::attribut::location{

enum ID{
  XYZ = 0,
  RGBA = 1,
  UV = 2,
};

}

//Data attribut binding
namespace vk::attribut::binding{

enum ID{
  XYZ = 0,
  RGBA = 1,
  UV = 2,
};

}
