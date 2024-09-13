#pragma once


namespace vk::renderpass{

enum Target{
  SHADER = 0,
  TRANSFER = 1,
  PRESENTATION = 2,
};

enum Attachment_id{
  ID_COLOR = 0,
  ID_DEPTH = 1,
  ID_TEXTURE = 2,
};


/*
  Attachment index is defined as follow:
    - 0 color
    - 1 depth
    - 2 texture

    - 0 color
    - 1 color
    - 2 color resolve
    - 3 depth
    - 4 texture
*/

}
