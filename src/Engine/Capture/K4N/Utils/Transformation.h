#pragma once

#include <Utility/Specific/common.h>
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavdevice/avdevice.h>
}

namespace k4n::utils{


class Transformation
{
public:
  //Constructor / Destructor
  Transformation();
  ~Transformation();

public:
  //Main function
  mat4 get_matrix_from_file(string path);
  bool is_json_file(const std::string& path);

private:

};

}
