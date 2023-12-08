#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <iostream>
#include <UTL_base/data::Struct_image.h>


namespace image{
  //---------------------------

  data::Struct_image load_image(std::string path);

  //---------------------------
}

#endif
