#pragma once

#include <Utility/Specific/common.h>
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavdevice/avdevice.h>
}

namespace k4n{


class Transformation
{
public:
  //Constructor / Destructor
  Transformation();
  ~Transformation();

public:
  //Main function
  void truc(string path);

private:

};

}
