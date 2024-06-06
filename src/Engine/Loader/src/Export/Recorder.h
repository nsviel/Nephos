#pragma once

#include <Loader/src/Base/Recorder.h>
#include <string>
#include <vector>

namespace ldr{class Node;}
namespace ldr{class Structure;}
namespace ldr::base{class Recorder;}
namespace ldr::base{class Recorder;}
namespace dat::base{class Entity;}


namespace ldr::io{

class Recorder
{
public:
  //Constructor / Destructor
  Recorder(ldr::Node* node_loader);
  ~Recorder();

public:
  //Main functions
  void insert_recorder(ldr::base::Recorder* recorder);

  //Subfunction
  bool is_format_supported(std::string format);
  std::vector<std::string> get_supported_format();

private:
  ldr::Structure* ldr_struct;

  std::vector<ldr::base::Recorder*> vec_recorder;
};

}
