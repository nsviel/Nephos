#pragma once


namespace vk::renderpass{

enum Target{
  SHADER = 0,
  TRANSFER = 1,
  PRESENTATION = 2,
};

}

//Renderpass attachment index
namespace vk::attachment{

enum ID{
  COLOR = 0,
  DEPTH = 1,
  TEXTURE = 2,
};

}
