#pragma once

#include <string>


namespace dyn::recorder{

enum Mode{
  MKV = 0,
  PLY = 1,
};

struct Structure{
  //---------------------------

  std::string folder = "../media/record/ply";
  std::string filename = "capture";
  std::string path = "";

  bool enable = false;
  int mode = dyn::recorder::PLY;
  double file_size = 0;
  float ts_rec = 0;
  float ts_beg;

  //---------------------------
};

}
