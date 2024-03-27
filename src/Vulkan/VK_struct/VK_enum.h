#pragma once

#include <Utility/Specific/Common.h>


enum attachment_idx{
  ATTACHMENT_INDEX_COLOR = 0,
  ATTACHMENT_INDEX_DEPTH = 1,
  ATTACHMENT_INDEX_COLOR_RESOLVE = 2,
};

enum binding_idx{
  BINDING_UNIFORM_BUFFER = 0,
  BINDING_TEXTURE = 1,
};

enum vertex_idx{
  VERTEX_LOCATION_POSITION = 0,
  VERTEX_LOCATION_NORMAL = 1,
  VERTEX_LOCATION_COLOR = 2,
};
